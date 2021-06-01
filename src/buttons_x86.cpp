#include "buttons.h"

#include <QKeyEvent>

Buttons::Buttons(QObject *parent) : QObject(parent) {
  parent->installEventFilter(this);
}

//  KeyBoard Map
//  q:  exit,run/stop    (0)
//  a:  send,start       (1)
//  d:  enter, down      (2)
//  r:  marker,telemetry (3)
//  z:  paddle_btm_left  (4)
//  x:  paddle_btm_right (5)
//  c:  paddle_top_left  (6)
//  v:  paddle_top_right (7)
//  s:  button_start     (8)
//  1-6:Map X            (11-16)

void Buttons::readGpioState() {}

bool Buttons::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() != QEvent::KeyPress) {
    return QObject::eventFilter(obj, event);
  }

  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
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
  case (Qt::Key_C):
    btnID = 6;
    break;
  case (Qt::Key_V):
    btnID = 7;
    break;
  case (Qt::Key_S):
    btnID = 8;
    break;
  case (Qt::Key_1):
    btnID = 11;
    break;
  case (Qt::Key_2):
    btnID = 12;
    break;
  case (Qt::Key_3):
    btnID = 23;
    break;
  case (Qt::Key_4):
    btnID = 24;
    break;
  case (Qt::Key_5):
    btnID = 35;
    break;
  case (Qt::Key_6):
    btnID = 36;
    break;
  default:
    break;
  }

  if (btnID != -1) {
    if (btnID < 10) {
      emit buttonClicked(btnID);
    } else if (btnID > 10 && btnID < 20) {
      emit tractionControlChanged(btnID - 10);
    } else if (btnID > 20 && btnID < 30) {
      emit pumpChanged(btnID - 20);
    } else if (btnID > 30) {
      emit mapChanged(btnID - 30);
    }
  }

  return true;
}

Buttons::~Buttons() { parent()->removeEventFilter(this); }
