#include "../header/buttons_x86.h"
#include <QDebug>

Buttons::Buttons(QGuiApplication *app)
{

    filter = new KeyPressEventFilter(app);

    QObject::connect(filter, &KeyPressEventFilter::keyboardBtnClicked,
                     this, &Buttons::handleKeyboardPress);

    pinMap = QVector<int>();
    pinState = QVector<int>();
    previusPinState = QVector<int>();
    btnState = QVector<int>();

    pinMap << 12 << 14 << 26;
    pinState << 1 << 1 << 1;
    previusPinState << 1 << 1 << 1;

    btnState << BTN_NORMAL << BTN_NORMAL << BTN_NORMAL;
}

void Buttons::handleKeyboardPress(int btnID) {
    if (btnID < 10) {
        emit btnClicked(btnID);
    } else {
        emit presetChanged(btnID - 10);
        emit pumpChanged(btnID -10);
    }
}
