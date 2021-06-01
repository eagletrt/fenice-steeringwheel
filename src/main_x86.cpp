#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "buttons.h"
#include "canbus.h"
#include "carstatus.h"
#include "leds.h"
#include "steering.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  sDebug("main") << "running on x86!";

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
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  engine.addImportPath(QStringLiteral("qrc:/"));

  Buttons buttons(&app);
  CarStatus carStatus(&app);
  Canbus canInterface(&carStatus, &app);

  QObject::connect(&buttons, &Buttons::mapChanged, &carStatus,
                   &CarStatus::changeMap);

  engine.rootContext()->setContextProperty("Buttons", &buttons);
  engine.rootContext()->setContextProperty("CAN", &canInterface);
  engine.rootContext()->setContextProperty("CarStatus", &carStatus);

  engine.load(url);

  return app.exec();
}
