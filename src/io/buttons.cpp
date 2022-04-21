#include "io/buttons.h"

#include <QMetaEnum>

#include "global.h"
#include "mcp23017.h"
#include "wiringPi.h"

QHash<int, int> buttonIds{
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
  wiringPiSetup();
  mcp23017Setup(100, 0x20); // manettino left + manettino right
  mcp23017Setup(116, 0x27); // manettino center + paddles top + paddles bottom +
                            // buttons top + buttons bottom

  m_button_pins_state = QVector<int>();
  m_button_pins_state_old = QVector<int>();
  m_manettino_pins_state = QVector<int>();
  m_manettino_pins_state_old = QVector<int>();

  m_button_state = QVector<States>();
  m_timers = QVector<QElapsedTimer>();

  m_button_action = -1;
  m_manettino_right_old = -1;
  m_manettino_left_old = -1;
  m_manettino_center_old = -1;
  m_manettino_right = -1;
  m_manettino_left = -1;
  m_manettino_center = -1;

  m_switch_timer = QElapsedTimer();
  m_switch_timer.start();

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
    m_timers.append(QElapsedTimer());
  }

  for (int i = 0; i < m_manettino_pins.size(); i++) {
    pinMode(m_manettino_pins[i], INPUT);
    pullUpDnControl(m_manettino_pins[i], PUD_UP);

    m_manettino_pins_state.append(1);
    m_manettino_pins_state_old.append(1);
  }

  // Setup signal / slot mechanism
  m_poll_timer = new QTimer(this);
  connect(m_poll_timer, SIGNAL(timeout()), this, SLOT(readGpioState()));
  m_poll_timer->start(50);
}

void Buttons::read_gpio_state() {
  for (int i = 0; i < m_button_pins.size(); i++) {
    m_button_pins_state[i] = digitalRead(m_button_pins.at(i));

    if (m_button_pins_state.at(i) != m_button_pins_state_old.at(i)) {
      m_button_action = -1;
      m_manettino_left = -1;
      m_manettino_center = -1;
      m_manettino_right = -1;

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

      int buttonId = buttonIds[m_button_pins[i]];
      if (m_button_action == BUTTON_PRESSED) {
        emit button_pressed(buttonId);
        m_timers[i].restart();
      } else {
        emit button_released(buttonId);
        if (m_timers[i].elapsed() < 500) {
          emit button_clicked(buttonId);
        } else {
          emit button_long_clicked(buttonId);
        }
      }
    }
  }

  m_button_pins_state_old = m_button_pins_state;

  for (int i = 0; i < m_manettino_pins.size(); i++) {
    m_manettino_pins_state[i] = digitalRead(m_manettino_pins.at(i));

    if (m_manettino_pins_state[i] != m_manettino_pins_state_old[i]) {
      if (m_manettino_pins[i] >= Gpio::GPIO_MANETTINO_LEFT_START &&
          m_manettino_pins[i] <= Gpio::GPIO_MANETTINO_LEFT_END) {
        this->m_manettino_left = m_manettino_pins[i] - Gpio::GPIO_MANETTINO_LEFT_START;
      } else if (m_manettino_pins[i] >= Gpio::GPIO_MANETTINO_CENTER_START &&
                 m_manettino_pins[i] <= Gpio::GPIO_MANETTINO_CENTER_END) {
        this->m_manettino_center = m_manettino_pins[i] - Gpio::GPIO_MANETTINO_CENTER_START;
      } else if (m_manettino_pins[i] >= Gpio::GPIO_MANETTINO_RIGHT_START &&
                 m_manettino_pins[i] <= Gpio::GPIO_MANETTINO_RIGHT_END) {
        this->m_manettino_right = m_manettino_pins[i] - Gpio::GPIO_MANETTINO_RIGHT_START;
      }

      if ((m_manettino_center != -1 && m_manettino_center != m_manettino_center_old) ||
          (m_manettino_left != -1 && m_manettino_left != m_manettino_left_old) ||
          (m_manettino_right != -1 && m_manettino_right != m_manettino_right_old)) {
        int elapsed = m_switch_timer.restart();
        if (elapsed > 10) {
          if (m_manettino_left != -1 && m_manettino_left != m_manettino_left_old) {
            emit manettino_left_changed(m_manettino_left);
            m_manettino_left_old = m_manettino_left;
          }
          if (m_manettino_center != -1 && m_manettino_center != m_manettino_center_old) {
            emit manettino_center_changed(m_manettino_center);
            m_manettino_center_old = m_manettino_center;
          }
          if (m_manettino_right != -1 && m_manettino_right != m_manettino_right_old) {
            emit manettino_right_changed(m_manettino_right);
            m_manettino_right_old = m_manettino_right;
          }
        }
      }
    }
  }

  m_manettino_pins_state_old = m_manettino_pins_state;
}

bool Buttons::eventFilter(QObject *, QEvent *) { return false; }

Buttons::~Buttons() { delete m_poll_timer; }
