#include <QDebug>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QThread>

#include "buttons_x86.h"

#include <QCanBus>

#include "canbus.h"
#include "carstatus.h"
#include "console.h"
#include "graphics.h"

int main(int argc, char *argv[]) {
  qDebug() << "Running x86";

  QGuiApplication app(argc, argv);
  QQuickView *view = new QQuickView();

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

  view->rootContext()->setContextProperty("Buttons", &buttons);
  view->rootContext()->setContextProperty("CAN", &canInterface);
  view->rootContext()->setContextProperty("CarStatus", &carStatus);

  view->setSource(QUrl("qrc:///qml/src/Main.qml"));

  //    QThread* threadG = new QThread();
  Graphics *graphics = new Graphics(view);
  //    graphics->moveToThread(threadG);

  //    QObject::connect(threadG, SIGNAL(started()),
  //                     graphics, SLOT(startGraphics()));

  //    threadG->start();
  graphics->startGraphics();

  return app.exec();
}
