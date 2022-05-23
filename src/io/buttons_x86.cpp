#include "io/buttons.h"

#include <QKeyEvent>

#include "global.h"

QHash<int, int> button_ids{{Qt::Key_D, Buttons::Input::BUTTON_TOP_LEFT},
                           {Qt::Key_A, Buttons::Input::BUTTON_BOTTOM_LEFT},
                           {Qt::Key_F, Buttons::Input::BUTTON_TOP_RIGHT},
                           {Qt::Key_S, Buttons::Input::BUTTON_BOTTOM_RIGHT},
                           {Qt::Key_C, Buttons::Input::PADDLE_TOP_LEFT},
                           {Qt::Key_Z, Buttons::Input::PADDLE_BOTTOM_LEFT},
                           {Qt::Key_V, Buttons::Input::PADDLE_TOP_RIGHT},
                           {Qt::Key_X, Buttons::Input::PADDLE_BOTTOM_RIGHT},
                           // {Qt::Key_???, Buttons::Input::BUTTON_START_STOP},
                           {Qt::Key_1, 11},
                           {Qt::Key_2, 12},
                           {Qt::Key_3, 13},
                           {Qt::Key_4, 14},
                           {Qt::Key_5, 15},
                           {Qt::Key_6, 16},
                           {Qt::Key_7, 17},
                           {Qt::Key_8, 18},
                           {Qt::Key_9, 19},
                           {Qt::Key_0, 20}};

Buttons::Buttons(QObject *parent) : QObject(parent) {
  m_timers = QVector<QElapsedTimer>();
  for (int i = 0; i < button_ids.size(); i++) {
    m_timers.append(QElapsedTimer());
  }
}

//  Keyboard Map
//  q:          exit, run / stop  (0)
//  a:          send, start       (1)
//  d:          enter, down       (2)
//  r:          marker, telemetry (3)
//  z:          paddle_btm_left   (4)
//  x:          paddle_btm_right  (5)
//  c:          paddle_top_left   (6)
//  v:          paddle_top_right  (7)
//  s:          button_start      (8)
//  1-9:        map               (11-20)
//  1-9 + ctrl: pump              (21-30)
//  1-9 + alt:  traction_control  (31-40)

void Buttons::read_gpio_state() {}

bool Buttons::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease) {
    return QObject::eventFilter(obj, event);
  }

  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

  if (button_ids.find(keyEvent->key()) == button_ids.end()) {
    // not included in the captured keys
    return QObject::eventFilter(obj, event);
  }

  int buttonId = button_ids[keyEvent->key()];

  bool ctrl = (keyEvent->modifiers() & Qt::ControlModifier) != 0;
  bool alt = (keyEvent->modifiers() & Qt::AltModifier) != 0;

  if (!alt && ctrl) {
    buttonId += 10;
  } else if (alt && !ctrl) {
    buttonId += 20;
  }

  if (buttonId != -1) {
    if (buttonId < 10) {
      if (event->type() == QEvent::KeyPress && !keyEvent->isAutoRepeat()) {
        emit button_pressed(buttonId);
        m_timers[buttonId].restart();
      } else if (event->type() == QEvent::KeyRelease && !keyEvent->isAutoRepeat()) {
        emit button_released(buttonId);
        if (m_timers[buttonId].elapsed() < 500) {
          emit button_clicked(buttonId);
        } else {
          emit button_long_clicked(buttonId);
        }
      }
    } else if (event->type() == QEvent::KeyPress) {
      if (buttonId > 10 && buttonId <= 20) {
        emit manettino_right_changed(buttonId - 11);
      } else if (buttonId > 20 && buttonId <= 30) {
        emit manettino_left_changed(buttonId - 21);
      } else if (buttonId > 30) {
        emit manettino_center_changed(buttonId - 31);
      }
    }
  }

  return true;
}

Buttons::~Buttons() { parent()->removeEventFilter(this); }
