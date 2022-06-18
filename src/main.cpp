#include <QFontDatabase>
#include <QGuiApplication>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <QWindow>

#ifdef S_OS_RASPBERRY
#include <wiringPi.h>
#endif

#include "global.h"

#include "io/buttons.h"
#include "io/leds.h"
#include "io/ptt.h"

#include "can/bus.h"

#include "car/das.h"
#include "car/hv.h"
#include "car/lv.h"
#include "car/state.h"

#include "ui/emulator.h"
#include "ui/speedometer.h"

#ifdef Q_OS_LINUX
#include <signal.h>

void quitGracefully(QVector<int> sigs) {
  auto handler = [](int sig) -> void {
    sDebug("main") << "quitting the application with signal" << sig;
    QCoreApplication::quit();
  };

  sigset_t blocking_mask;
  sigemptyset(&blocking_mask);
  for (auto sig : sigs)
    sigaddset(&blocking_mask, sig);

  struct sigaction sa;
  sa.sa_mask = blocking_mask;
  sa.sa_flags = 0;
  sa.sa_handler = handler;

  for (auto sig : sigs)
    sigaction(sig, &sa, nullptr);
}
#endif

int main(int argc, char *argv[]) {
#ifdef Q_OS_MAC
  // Forcibly disable any DPI scaling on macOS
  QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
  if (qEnvironmentVariableIsEmpty("QT_FONT_DPI")) {
    qputenv("QT_FONT_DPI", "84");
  }
#endif

#ifdef S_OS_RASPBERRY
  wiringPiSetup();
#endif

  // setup global logging, also reflected in the UI
  qInstallMessageHandler(Global::messageHandler);

  sDebug("main") << "running on" << QSysInfo::currentCpuArchitecture();

  QGuiApplication app(argc, argv);

  const QUrl url(QStringLiteral("qrc:///qml/Main.qml"));

  QQmlApplicationEngine engine(&app);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QGuiApplication::exit(1);
      },
      Qt::QueuedConnection);

  engine.addImportPath(QStringLiteral("qrc:/"));

  QFontDatabase::addApplicationFont("qrc:/qml/font/Mono-Regular.ttf");
  QFontDatabase::addApplicationFont("qrc:/qml/font/Mono-Bold.ttf");

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Style.qml"), "Const", 1, 0, "Style");
  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Input.qml"), "Const", 1, 0, "Input");
  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Utils.qml"), "Const", 1, 0, "Utils");

  qmlRegisterUncreatableType<DAS>("Car", 1, 0, "DAS", "Not creatable as it is an enum type.");
  qmlRegisterUncreatableType<HV>("Car", 1, 0, "HV", "Not creatable as it is an enum type.");
  qmlRegisterUncreatableType<LV>("Car", 1, 0, "LV", "Not creatable as it is an enum type.");
  qmlRegisterType<Speedometer>("Car", 1, 0, "Speedometer");
  qmlRegisterType<Emulator>("Car", 1, 0, "Emulator");

  Leds *leds = new Leds(&engine);
  Buttons *buttons = new Buttons(&engine);
  CanBus *canBus = new CanBus(&engine);
  State *state = new State(&engine);
  Ptt *ptt = new Ptt(&engine);

  QObject::connect(canBus, &CanBus::message_received, state, &State::handle_message);
  QObject::connect(state, &State::send_message, canBus, &CanBus::send_message);

  QObject::connect(buttons, &Buttons::manettino_left_changed, state->steering(), &Steering::manettino_left_changed);
  QObject::connect(buttons, &Buttons::manettino_right_changed, state->steering(), &Steering::manettino_right_changed);
  QObject::connect(buttons, &Buttons::button_pressed, state->steering(), &Steering::button_pressed);
  QObject::connect(buttons, &Buttons::button_released, state->steering(), &Steering::button_released);

  QObject::connect(buttons, &Buttons::button_clicked, state->das(), &DAS::button_clicked);

  QObject::connect(buttons, &Buttons::button_clicked, state->telemetry(), &Telemetry::button_clicked);
  QObject::connect(buttons, &Buttons::button_long_clicked, state->telemetry(), &Telemetry::button_long_clicked);

  QObject::connect(state->steering(), &Steering::ptt_changed, leds, [&](bool ptt_value) {
    leds->set_left_brightness(7, ptt_value ? 0xFF : 0x0);
    if (ptt_value) {
      ptt->start();
    } else {
      ptt->stop();
    }
  });

  QObject::connect(state->telemetry(), &Telemetry::status_changed, leds,
                   [&](bool status) { leds->set_right_brightness(6, status == primary_Toggle_ON ? 0xFF : 0x0); });

  leds->set_left_brightness(0, 0xFF);
  leds->set_left_brightness(3, 0xFF);

  leds->set_right_brightness(0, 0xFF);
  leds->set_right_brightness(3, 0xFF);

#ifdef S_OS_X86
  app.installEventFilter(buttons);
#endif

  canBus->start();

  engine.rootContext()->setContextProperty("Leds", leds);
  engine.rootContext()->setContextProperty("Buttons", buttons);
  engine.rootContext()->setContextProperty("CanBus", canBus);
  engine.rootContext()->setContextProperty("Car", state);

  engine.rootContext()->setContextProperty("Global", &Global::instance());

  engine.load(url);

#ifdef Q_OS_LINUX
  quitGracefully({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
#endif

  sDebug("main") << "fenice steering wheel v0.0.0";

  // print the IP of the steering-wheels

  QTimer::singleShot(5000, &engine, [&]() {
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : qAsConst(addresses)) {
      if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback())
        sDebug("main") << "ip address" << address.toString();
    }
  });

  return app.exec();
}
