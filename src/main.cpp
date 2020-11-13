#include <QDebug>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QThread>

#include "buttons.h"

#include "canbus.h"
#include "carstatus.h"
#include "console.h"
#include "graphics.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // ?

  qDebug() << "Running ARM";

  QGuiApplication app(argc, argv);
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
  Console logger;
  CarStatus carStatus;
  Canbus canInterface(&carStatus);

  QObject::connect(&buttons, &Buttons::mapChanged, &carStatus,
                   &CarStatus::changeMap);

  QObject::connect(&buttons, &Buttons::pumpChanged, &carStatus,
                   &CarStatus::changePump);

  QObject::connect(&buttons, &Buttons::tcChanged, &carStatus,
                   &CarStatus::changeTc);

  engine.rootContext()->setContextProperty("Buttons", &buttons);
  engine.rootContext()->setContextProperty("CAN", &canInterface);
  engine.rootContext()->setContextProperty("CarStatus", &carStatus);

  engine.load(url);

  // QThread *threadG = new QThread();
  // Graphics *graphics = new Graphics(view);
  // graphics->moveToThread(threadG);

  // QObject::connect(threadG, SIGNAL(started()), graphics,
  // SLOT(startGraphics()));

  // threadG->start();

  return app.exec();
}
