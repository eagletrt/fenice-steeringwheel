#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "io/buttons.h"
#include "io/leds.h"
#include "global.h"

#include "can/bus.h"
#include "car/state.h"

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

  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Style.qml"), "Const", 1, 0, "Style");
  qmlRegisterSingletonType(QUrl("qrc:///qml/const/Input.qml"), "Const", 1, 0, "Input");
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
  CanBus bus(&app);
  State state(&app);

  bus.start();

  engine.rootContext()->setContextProperty("Leds", &leds);
  engine.rootContext()->setContextProperty("Buttons", &buttons);
  engine.rootContext()->setContextProperty("CanBus", &bus);

  engine.rootContext()->setContextProperty("Global", &Global::instance());

  engine.load(url);

#ifdef Q_OS_LINUX
  quitGracefully({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
#endif

  return app.exec();
}
