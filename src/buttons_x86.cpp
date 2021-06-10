#include <QKeyEvent>

#include "buttons.h"
#include "steering.h"

QHash<int, int> buttonIds{
    {Qt::Key_Q, 0}, {Qt::Key_A, 1}, {Qt::Key_D, 2}, {Qt::Key_R, 3},
    {Qt::Key_Z, 4}, {Qt::Key_X, 5}, {Qt::Key_C, 6}, {Qt::Key_V, 7},
};

Buttons::Buttons(QObject *parent) : QObject(parent) { parent->installEventFilter(this); }

//  Keyboard Map
//  q:   exit,run/stop    (0)
//  a:   send,start       (1)
//  d:   enter, down      (2)
//  r:   marker,telemetry (3)
//  z:   paddle_btm_left  (4)
//  x:   paddle_btm_right (5)
//  c:   paddle_top_left  (6)
//  v:   paddle_top_right (7)
//  s:   button_start     (8)
//  1-6: map X            (11-16)

void Buttons::readGpioState() {}

bool Buttons::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() != QEvent::KeyPress) {
    return QObject::eventFilter(obj, event);
  }

  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

  if (buttonIds.find(keyEvent->key()) == buttonIds.end()) {
    // not included in the captuerd keys
    return QObject::eventFilter(obj, event);
  }

  int buttonId = buttonIds[keyEvent->key()];
  sDebug("button") << keyEvent->key() << buttonId << buttonIds;

  if (buttonId != -1) {
    if (buttonId < 10) {
      emit buttonClicked(buttonId);
    } else if (buttonId > 10 && buttonId < 20) {
      emit tractionControlChanged(buttonId - 10);
    } else if (buttonId > 20 && buttonId < 30) {
      emit pumpChanged(buttonId - 20);
    } else if (buttonId > 30) {
      emit mapChanged(buttonId - 30);
    }
  }

  return true;
}

Buttons::~Buttons() { parent()->removeEventFilter(this); }
