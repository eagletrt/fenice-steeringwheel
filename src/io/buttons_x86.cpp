#include "io/buttons.h"

#include <QKeyEvent>

#include "global.h"

QHash<int, int> buttonIds{
    {Qt::Key_D, Buttons::Input::BUTTON_TOP_LEFT},  {Qt::Key_A, Buttons::Input::BUTTON_BOTTOM_LEFT},
    {Qt::Key_F, Buttons::Input::BUTTON_TOP_RIGHT}, {Qt::Key_S, Buttons::Input::BUTTON_BOTTOM_RIGHT},
    {Qt::Key_C, Buttons::Input::PADDLE_TOP_LEFT},  {Qt::Key_Z, Buttons::Input::PADDLE_BOTTOM_LEFT},
    {Qt::Key_V, Buttons::Input::PADDLE_TOP_RIGHT}, {Qt::Key_X, Buttons::Input::PADDLE_BOTTOM_RIGHT},
};

Buttons::Buttons(QObject *parent) : QObject(parent) {}

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
  if (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease) {
    return QObject::eventFilter(obj, event);
  }

  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

  if (buttonIds.find(keyEvent->key()) == buttonIds.end()) {
    // not included in the captured keys
    return QObject::eventFilter(obj, event);
  }

  int buttonId = buttonIds[keyEvent->key()];

  if (buttonId != -1) {
    if (buttonId < 10) {
      if (event->type() == QEvent::KeyPress && !keyEvent->isAutoRepeat()) {
        emit buttonPressed(buttonId);
      } else if (event->type() == QEvent::KeyRelease && !keyEvent->isAutoRepeat()) {
        emit buttonReleased(buttonId);
      }
    } else if (event->type() == QEvent::KeyPress) {
      if (buttonId > 10 && buttonId < 20) {
        emit tractionControlChanged(buttonId - 10);
      } else if (buttonId > 20 && buttonId < 30) {
        emit pumpChanged(buttonId - 20);
      } else if (buttonId > 30) {
        emit mapChanged(buttonId - 30);
      }
    }
  }

  return true;
}

Buttons::~Buttons() { parent()->removeEventFilter(this); }
