#include <QGuiApplication>
#include <QDebug>
#include <QQuickView>
#include <QQmlContext>

#include "../header/buttons.h"

#include "../header/console.h"
#include "../header/canbus.h"
#include "../header/carstatus.h"

int main(int argc, char* argv[])
{
    qDebug() << "Running ARM";

    QGuiApplication app(argc, argv);
    QQuickView* view = new QQuickView();

    Buttons buttons(&app);
    Console logger;
    CarStatus carStatus;
    Canbus canInterface(&carStatus);

    QObject::connect(&buttons, &Buttons::mapChanged,
                     &carStatus, &CarStatus::changeMap);

    QObject::connect(&buttons, &Buttons::pumpChanged,
                     &carStatus, &CarStatus::changePump);

    QObject::connect(&buttons, &Buttons::tcChanged,
                     &carStatus, &CarStatus::changeTc);

    view->rootContext()->setContextProperty("Buttons", &buttons);
    view->rootContext()->setContextProperty("CAN", &canInterface);
    view->rootContext()->setContextProperty("CarStatus", &carStatus);

    view->setSource(QUrl("qrc:///qml/main.qml"));
    view->show();

    return app.exec();
}
