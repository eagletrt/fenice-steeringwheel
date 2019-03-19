#include "../header/keypresseventfilter.h"

#include <QDebug>
#include <QKeyEvent>

KeyPressEventFilter::KeyPressEventFilter(QObject * parent)
    : QObject(parent)
{
    parent->installEventFilter(this);
}

bool KeyPressEventFilter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() != QEvent::KeyPress) {
        return QObject::eventFilter(obj, event);
    }

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    int btnID = -1;

    switch (keyEvent->key()) {
        case (Qt::Key_Q):
            btnID = 0;
            break;
        case (Qt::Key_A):
            btnID = 1;
            break;
        case (Qt::Key_D):
            btnID = 2;
            break;
        case (Qt::Key_R):
            btnID = 3;
            break;
        case (Qt::Key_Z):
            btnID = 4;
            break;
        case (Qt::Key_X):
            btnID = 5;
           break;
        case (Qt::Key_1):
            btnID = 11;
            break;
        case (Qt::Key_2):
            btnID = 12;
            break;
        case (Qt::Key_3):
            btnID = 13;
            break;
        case (Qt::Key_4):
            btnID = 14;
            break;
        case (Qt::Key_5):
            btnID = 15;
            break;
        case (Qt::Key_6):
            btnID = 16;
            break;
        default:
            break;
    }

    if (btnID != -1) {
        emit keyboardBtnClicked(btnID);
    }

    return true;
}
