#include <QGuiApplication>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "global.h"

#include "io/buttons.h"
#include "io/leds.h"

#include "can/bus.h"

#include "car/ecu.h"
#include "car/hv.h"
#include "car/lv.h"
#include "car/state.h"

#ifdef EASTER_EGG
#include "game/extension.h"
#endif

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

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Style.qml"), "Const", 1, 0, "Style");
  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Input.qml"), "Const", 1, 0, "Input");
  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Utils.qml"), "Const", 1, 0, "Utils");

  qmlRegisterUncreatableType<ECU>("Car", 1, 0, "ECU", "Not creatable as it is an enum type.");
  qmlRegisterUncreatableType<HV>("Car", 1, 0, "HV", "Not creatable as it is an enum type.");
  qmlRegisterUncreatableType<LV>("Car", 1, 0, "LV", "Not creatable as it is an enum type.");

#ifdef EASTER_EGG
  qmlRegisterType<Extension>("Extension", 1, 0, "Extension");
  engine.rootContext()->setContextProperty("EASTER_EGG", QVariant(true));
#else
  engine.rootContext()->setContextProperty("EASTER_EGG", QVariant(false));
#endif

  Leds *leds = new Leds(&engine);
  Buttons *buttons = new Buttons(&engine);
  CanBus *canBus = new CanBus(&engine);
  State *state = new State(&engine);

  QObject::connect(buttons, &Buttons::manettinoLeftChanged, state->steering(), &Steering::onManettinoLeftChanged);
  QObject::connect(buttons, &Buttons::manettinoCenterChanged, state->telemetry(), &Telemetry::onManettinoCenterChanged);
  QObject::connect(buttons, &Buttons::manettinoRightChanged, state->steering(), &Steering::onManettinoRightChanged);

  QObject::connect(canBus, &CanBus::messageReceived, state, &State::handleMessage);
  QObject::connect(state, &State::sendMessage, canBus, &CanBus::sendMessage);

  QObject::connect(buttons, &Buttons::buttonPressed, state->steering(), &Steering::onButtonPressed);
  QObject::connect(buttons, &Buttons::buttonReleased, state->steering(), &Steering::onButtonReleased);

  QObject::connect(buttons, &Buttons::buttonReleased, state->steering(), &Steering::onButtonReleased);

  QObject::connect(buttons, &Buttons::buttonClicked, state->telemetry(), &Telemetry::onButtonClicked);
  QObject::connect(buttons, &Buttons::buttonLongClicked, state->telemetry(), &Telemetry::onButtonLongClicked);

  QObject::connect(state->steering(), &Steering::pttChanged, leds,
                   [&](bool ptt) { leds->setLeftBrightness(7, ptt ? 0xFF : 0x0); });

  QObject::connect(state->telemetry(), &Telemetry::statusChanged, leds, [&](Telemetry::TlmStatus status) {
    leds->setRightBrightness(6, status == Telemetry::TlmStatus::TLM_STATUS_ON ? 0xFF : 0x0);
  });

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

  QTimer::singleShot(1000, &engine, [&]() {
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : qAsConst(addresses)) {
      if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback())
        sDebug("main") << "IP address" << address.toString();
    }
  });

  return app.exec();
}
