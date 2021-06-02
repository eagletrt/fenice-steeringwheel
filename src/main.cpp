#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "buttons.h"
#include "canbus.h"
#include "carstatus.h"
#include "leds.h"
#include "steering.h"

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
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qInstallMessageHandler(Steering::messageHandler);

  sDebug("main") << "running on ARM!";

  QGuiApplication app(argc, argv);

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Style.qml"), "Const", 1, 0,
                           "Style");

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/ButtonIds.qml"), "Const", 1,
                           0, "ButtonIds");

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

  Leds leds(&engine);

  Buttons buttons(&engine);
  CarStatus carStatus(&engine);
  Canbus canInterface(&carStatus, &engine);

  QObject::connect(&buttons, &Buttons::mapChanged, &carStatus,
                   &CarStatus::changeMap);

  QObject::connect(&buttons, &Buttons::pumpChanged, &leds, &Leds::pumpChanged);

  QObject::connect(&buttons, &Buttons::tractionControlChanged, &leds,
                   &Leds::tractionControlChanged);

  engine.rootContext()->setContextProperty("Buttons", &buttons);
  engine.rootContext()->setContextProperty("CAN", &canInterface);
  engine.rootContext()->setContextProperty("CarStatus", &carStatus);
  engine.rootContext()->setContextProperty("Leds", &leds);
  engine.rootContext()->setContextProperty("Steering", &Steering::instance());

  engine.load(url);

#ifdef Q_OS_LINUX
  quitGracefully({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
#endif

  return app.exec();
}
