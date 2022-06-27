#include "io/buttons.h"

#include <QMetaEnum>

#include "global.h"
#include "mcp23017.h"
#include "wiringPi.h"

QHash<int, int> button_ids{
    {Buttons::Gpio::GPIO_BUTTON_TOP_LEFT, Buttons::Input::BUTTON_TOP_LEFT},
    {Buttons::Gpio::GPIO_BUTTON_BOTTOM_LEFT, Buttons::Input::BUTTON_BOTTOM_LEFT},
    {Buttons::Gpio::GPIO_BUTTON_TOP_RIGHT, Buttons::Input::BUTTON_TOP_RIGHT},
    {Buttons::Gpio::GPIO_BUTTON_BOTTOM_RIGHT, Buttons::Input::BUTTON_BOTTOM_RIGHT},
    {Buttons::Gpio::GPIO_PADDLE_TOP_LEFT, Buttons::Input::PADDLE_TOP_LEFT},
    {Buttons::Gpio::GPIO_PADDLE_BOTTOM_LEFT, Buttons::Input::PADDLE_BOTTOM_LEFT},
    {Buttons::Gpio::GPIO_PADDLE_TOP_RIGHT, Buttons::Input::PADDLE_TOP_RIGHT},
    {Buttons::Gpio::GPIO_PADDLE_BOTTOM_RIGHT, Buttons::Input::PADDLE_BOTTOM_RIGHT},
    {Buttons::Gpio::GPIO_BUTTON_START_STOP, Buttons::Input::BUTTON_START_STOP},
};

Buttons::Buttons(QObject *parent) : QObject(parent) {
  // Init GPIO access
  mcp23017Setup(100, 0x20); // manettino left + manettino right
  mcp23017Setup(116, 0x27); // manettino center + paddles top + paddles bottom +
                            // buttons top + buttons bottom

  m_button_pins_state = QVector<quint8>();
  m_button_pins_state_old = QVector<quint8>();
  m_manettino_pins_state = QVector<quint8>();
  m_manettino_pins_state_old = QVector<quint8>();

  m_button_state = QVector<States>();

  m_switch_timer.start();
  m_manettino_elapsed_timer.start();

  m_button_pins = {
      25, // button center

      116, // paddle bottom right
      117, // paddle top right
      118, // paddle bottom left
      119, // paddle top left

      120, // button bottom left
      121, // button top right
      122, // button top left
      123, // button bottom right
  };

  m_manettino_pins = {
      100, 101, 102, 103, 104, 105, 106, 107, // manettino right
      108, 109, 110, 111, 112, 113, 114, 115, // manettino left
      124, 125, 126, 127, 128, 129, 130, 131, // manettino center
  };

  for (int i = 0; i < m_button_pins.size(); i++) {
    pinMode(m_button_pins[i], INPUT);
    pullUpDnControl(m_button_pins[i], PUD_UP);

    m_button_pins_state.append(1);
    m_button_pins_state_old.append(1);
    m_button_state.append(BUTTON_NORMAL);
  }

  for (int i = 0; i < m_manettino_pins.size(); i++) {
    pinMode(m_manettino_pins[i], INPUT);
    pullUpDnControl(m_manettino_pins[i], PUD_UP);

    m_manettino_pins_state.append(1);
    m_manettino_pins_state_old.append(1);
  }

  for (int i = 0; i < BUTTONS_LENGTH; i++) {
    m_pressed_elapsed_timers[i] = QElapsedTimer();
    m_long_pressed_timers[i] = new QTimer(this);
    m_long_pressed_timers[i]->callOnTimeout(this, [&]() -> void { emit button_long_pressed(i); });
    m_long_pressed_timers[i]->setInterval(500);
  }

  // Setup signal / slot mechanism
  m_poll_timer = new QTimer(this);
  connect(m_poll_timer, &QTimer::timeout, this, &Buttons::read_gpio_state);
  m_poll_timer->start(50);
}

void Buttons::read_gpio_state() {
  for (int i = 0; i < m_button_pins.size(); i++) {
    m_button_pins_state[i] = digitalRead(m_button_pins.at(i));

    if (m_button_pins_state.at(i) != m_button_pins_state_old.at(i)) {
      m_button_action = -1;

      switch (m_button_state.at(i)) {
      case BUTTON_NORMAL:
        m_button_state[i] = BUTTON_PRESSED;
        m_button_action = BUTTON_PRESSED;
        break;
      case BUTTON_PRESSED:
        m_button_state[i] = BUTTON_NORMAL;
        m_button_action = BUTTON_NORMAL;
        break;
      }

      int button_id = button_ids[m_button_pins[i]];
      if (m_button_action == BUTTON_PRESSED) {
        emit button_pressed(button_id);
        m_long_pressed_timers[button_id]->start();
        m_pressed_elapsed_timers[i].restart();
      } else {
        m_long_pressed_timers[button_id]->stop();
        emit button_released(button_id);
        if (m_pressed_elapsed_timers[i].elapsed() < LONG_PRESS) {
          emit button_clicked(button_id);
        } else {
          emit button_long_clicked(button_id);
        }
      }
    }
  }

  m_button_pins_state_old = m_button_pins_state;

  for (int i = 0; i < m_manettino_pins.size(); i++) {
    m_manettino_pins_state[i] = digitalRead(m_manettino_pins.at(i));

    if (m_manettino_pins_state[i] != m_manettino_pins_state_old[i] && m_manettino_pins_state[i] == 0) {
      if (m_manettino_pins[i] >= Gpio::GPIO_MANETTINO_LEFT_START &&
          m_manettino_pins[i] <= Gpio::GPIO_MANETTINO_LEFT_END) {
        m_manettino_left = m_manettino_pins[i] - Gpio::GPIO_MANETTINO_LEFT_START;
      } else if (m_manettino_pins[i] >= Gpio::GPIO_MANETTINO_CENTER_START &&
                 m_manettino_pins[i] <= Gpio::GPIO_MANETTINO_CENTER_END) {
        m_manettino_center = m_manettino_pins[i] - Gpio::GPIO_MANETTINO_CENTER_START;
      } else if (m_manettino_pins[i] >= Gpio::GPIO_MANETTINO_RIGHT_START &&
                 m_manettino_pins[i] <= Gpio::GPIO_MANETTINO_RIGHT_END) {
        m_manettino_right = m_manettino_pins[i] - Gpio::GPIO_MANETTINO_RIGHT_START;
      }
    }
  }

  if (m_switch_timer.elapsed() > MANETTINO_DEBOUNCE) {
    if (m_manettino_left != m_manettino_left_old) {
      m_manettino_left_state = m_manettino_left;
      emit manettino_left_changed(m_manettino_left);
    }
    m_manettino_left_old = m_manettino_left;

    if (m_manettino_center != m_manettino_center_old) {
      m_manettino_center_state = m_manettino_center;
      emit manettino_center_changed(m_manettino_center);
    }
    m_manettino_center_old = m_manettino_center;

    if (m_manettino_right != m_manettino_right_old) {
      m_manettino_right_state = m_manettino_right;
      emit manettino_right_changed(m_manettino_right);
    }

    m_manettino_right_old = m_manettino_right;

    m_switch_timer.restart();
  }

  if (m_manettino_elapsed_timer.elapsed() > MANETTINO_STATE_UPDATE) {
    emit manettino_left(m_manettino_left_state);
    emit manettino_center(m_manettino_center_state);
    emit manettino_right(m_manettino_right_state);
    m_manettino_elapsed_timer.restart();
  }

  m_manettino_pins_state_old = m_manettino_pins_state;
}

bool Buttons::eventFilter(QObject *, QEvent *) { return false; }

Buttons::~Buttons() { delete m_poll_timer; }
