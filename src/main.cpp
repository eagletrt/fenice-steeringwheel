#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "buttons.h"
#include "carstatus.h"
#include "leds.h"
#include "steering.h"

#include "can/canbus.h"

#ifdef Q_OS_LINUX
#include <signal.h>

void quitGracefully(QVector<int> sigs) {
  auto handler = [](int sig) -> void {
    sDebug("main") << "quit the application by signal" << sig;
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
//  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  qInstallMessageHandler(Steering::messageHandler);

  sDebug("main") << "running on" << QSysInfo::currentCpuArchitecture();

  QGuiApplication app(argc, argv);

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Style.qml"), "Const", 1, 0, "Style");

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/ButtonIds.qml"), "Const", 1, 0, "ButtonIds");

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Utils.qml"), "Const", 1, 0, "Utils");

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:///qml/Main.qml"));

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(1);
      },
      Qt::QueuedConnection);

  engine.addImportPath(QStringLiteral("qrc:/"));

  Leds leds(&app);
  Buttons buttons(&app);
  CarStatus carStatus(&app);
  CanBus canBus(&carStatus, &app);

  canBus.start();

  QObject::connect(&buttons, &Buttons::mapChanged, &carStatus, &CarStatus::changeMap);
  QObject::connect(&buttons, &Buttons::pumpChanged, &carStatus, &CarStatus::changePump);
  QObject::connect(&buttons, &Buttons::tractionControlChanged, &carStatus, &CarStatus::changeTractionControl);

  engine.rootContext()->setContextProperty("Leds", &leds);
  engine.rootContext()->setContextProperty("Buttons", &buttons);
  engine.rootContext()->setContextProperty("CarStatus", &carStatus);
  engine.rootContext()->setContextProperty("CanBus", &canBus);

  engine.rootContext()->setContextProperty("Steering", &Steering::instance());

  engine.load(url);

#ifdef Q_OS_LINUX
  quitGracefully({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
#endif

  return app.exec();
}
