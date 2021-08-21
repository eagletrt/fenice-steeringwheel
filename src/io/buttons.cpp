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
};

Buttons::Buttons(QObject *parent) : QObject(parent) {
  // Init GPIO access
  wiringPiSetup();
  mcp23017Setup(100, 0x20); // manettino left + manettino right
  mcp23017Setup(116, 0x27); // manettino center + paddles top + paddles bottom +
                            // buttons top + buttons bottom

  m_pin_state = QVector<int>();
  m_pin_state_old = QVector<int>();
  m_button_state = QVector<States>();

  m_button_action = -1;
  m_tc_old = -1;
  m_pump_old = -1;
  m_map_old = -1;
  m_tc = -1;
  m_pump = -1;
  m_map = -1;

  m_switch_timer = QElapsedTimer();
  m_switch_timer.start();

  m_switch_is_wrong = false;

  m_pins = {
      25, // button center

      100, 101, 102, 103, 104, 105, 106, 107, // manettino right
      108, 109, 110, 111, 112, 113, 114, 115, // manettino left

      116, // paddle bottom right
      117, // paddle top right
      118, // paddle bottom left
      119, // paddle top left

      120, // button bottom left
      121, // button top right
      122, // button top left
      123, // button bottom right

      124, 125, 126, 127, 128, 129, 130, 131, // manettino center
  };

  for (int i = 0; i < m_pins.size(); i++) {
    pinMode(m_pins[i], INPUT);
    pullUpDnControl(m_pins[i], PUD_UP);

    m_pin_state.append(1);
    m_pin_state_old.append(1);
    m_button_state.append(BUTTON_NORMAL);
  }

  // Setup signal/slot mechanism
  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(readGpioState()));
  m_timer->start(30);
}

void Buttons::readGpioState() {
  for (int i = 0; i < m_pins.size(); i++) {
    m_pin_state[i] = digitalRead(m_pins.at(i));

    if (m_pin_state.at(i) != m_pin_state_old.at(i)) {
      m_button_action = -1;
      m_pump = -1;
      m_map = -1;
      m_tc = -1;

      switch (m_button_state.at(i)) {
      case BUTTON_NORMAL:
        this->m_button_state[i] = BUTTON_PRESSED;
        this->m_button_action = BUTTON_PRESSED;
        break;
      case BUTTON_PRESSED:
        this->m_button_state[i] = BUTTON_NORMAL;
        this->m_button_action = BUTTON_NORMAL;
        break;
      }

      if (m_button_action == BUTTON_PRESSED) {
        emit buttonPressed(buttonIds[m_pins[i]]);
      } else {
        emit buttonReleased(buttonIds[m_pins[i]]);
        emit buttonClicked(buttonIds[m_pins[i]]);
      }

#ifdef QT_DEBUG
      QMetaEnum metaEnum = QMetaEnum::fromType<Buttons::Gpio>();
      QString name = metaEnum.valueToKey(m_pins[i]);
      if (name.length() > 0) {
        sDebug("buttons") << m_pins[i] << name << "changed state to:" << m_pin_state[i];
      } else {
        sDebug("buttons") << m_pins[i] << "changed state to:" << m_pin_state[i];
      }
#endif

      if (m_pins[i] >= Gpio::GPIO_MANETTINO_LEFT_START && m_pins[i] <= Gpio::GPIO_MANETTINO_LEFT_END) {
        this->m_pump = m_pins[i] - Gpio::GPIO_MANETTINO_LEFT_START;
      } else if (m_pins[i] >= Gpio::GPIO_MANETTINO_CENTER_START && m_pins[i] <= Gpio::GPIO_MANETTINO_CENTER_END) {
        this->m_map = m_pins[i] - Gpio::GPIO_MANETTINO_CENTER_START;
      } else if (m_pins[i] >= Gpio::GPIO_MANETTINO_RIGHT_START && m_pins[i] <= Gpio::GPIO_MANETTINO_RIGHT_END) {
        this->m_tc = m_pins[i] - Gpio::GPIO_MANETTINO_RIGHT_START;
      }

      if ((m_map != -1 && m_map != m_map_old) || (m_pump != -1 && m_pump != m_pump_old) ||
          (m_tc != -1 && m_tc != m_tc_old)) {
        int timeElapsed = m_switch_timer.restart();

        if (timeElapsed < 15) {
          m_switch_is_wrong = true;
        }

        if (!m_switch_is_wrong) {
          if (m_map != -1 && m_map != m_map_old) {
            emit mapChanged(m_map);
            m_map_old = m_map;
          }
          if (m_pump != -1 && m_pump != m_pump_old) {
            emit pumpChanged(m_pump);
            m_pump_old = m_pump;
          }
          if (m_tc != -1 && m_tc != m_tc_old) {
            emit tractionControlChanged(m_tc);
            m_tc_old = m_tc;
          }
        }

        m_switch_is_wrong = false;
      }
    }

    m_pin_state_old[i] = m_pin_state.at(i);
  }
}

bool Buttons::eventFilter(QObject *, QEvent *) {}

Buttons::~Buttons() { delete m_timer; }
