#include "../header/console.h"
#include <QDebug>

Console::Console() {
}

void Console::onClicked(int btnID) {
    qDebug() << "Button Clicked: " << btnID;
    qDebug() << "**************************";
}

void Console::onPressed(int btnID) {
    qDebug() << "Button Pressed:  " << btnID;
}

void Console::onReleased(int btnID) {
    qDebug() << "Button Released:  " << btnID;
}
