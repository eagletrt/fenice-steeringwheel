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
                           {Qt::Key_Return, Buttons::Input::BUTTON_START_STOP},
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
  for (int i = 0; i < BUTTONS_LENGTH; i++) {
    m_pressed_elapsed_timers[i] = QElapsedTimer();
    m_long_pressed_timers[i] = new QTimer(this);
    m_long_pressed_timers[i]->callOnTimeout(this, [&]() -> void { emit button_long_pressed(i); });
  }
}

void Buttons::read_gpio_state() {}

bool Buttons::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease) {
    return QObject::eventFilter(obj, event);
  }

  QKeyEvent *key_event = static_cast<QKeyEvent *>(event);

  if (button_ids.find(key_event->key()) == button_ids.end()) {
    // not included in the captured keys
    return QObject::eventFilter(obj, event);
  }

  int button_id = button_ids[key_event->key()];

  bool ctrl = (key_event->modifiers() & Qt::ControlModifier) != 0;
  bool alt = (key_event->modifiers() & Qt::AltModifier) != 0;

  if (!alt && ctrl) {
    button_id += 10;
  } else if (alt && !ctrl) {
    button_id += 20;
  }

  if (button_id != -1) {
    if (button_id < 10) {
      if (event->type() == QEvent::KeyPress && !key_event->isAutoRepeat()) {
        emit button_pressed(button_id);
        m_long_pressed_timers[button_id]->start();
        m_pressed_elapsed_timers[button_id].restart();
      } else if (event->type() == QEvent::KeyRelease && !key_event->isAutoRepeat()) {
        m_long_pressed_timers[button_id]->stop();
        emit button_released(button_id);
        if (m_pressed_elapsed_timers[button_id].elapsed() < 500) {
          emit button_clicked(button_id);
        } else {
          emit button_long_clicked(button_id);
        }
      }
    } else if (event->type() == QEvent::KeyPress) {
      if (button_id > 10 && button_id <= 20) {
        emit manettino_right_changed(button_id - 11);
        emit manettino_right(button_id - 11);
      } else if (button_id > 20 && button_id <= 30) {
        emit manettino_left_changed(button_id - 21);
        emit manettino_left(button_id - 11);
      } else if (button_id > 30) {
        emit manettino_center_changed(button_id - 31);
        emit manettino_center(button_id - 11);
      }
    }
  }

  return true;
}

Buttons::~Buttons() { parent()->removeEventFilter(this); }
