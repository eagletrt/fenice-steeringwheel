#include "buttons.h"

#include <QMetaEnum>

#include "mcp23017.h"
#include "steering.h"
#include "wiringPi.h"

QHash<int, int> buttonIds{
    {Buttons::Gpio::GPIO_BUTTON_TOP_LEFT, Buttons::ButtonIds::BUTTON_TOP_LEFT},
    {Buttons::Gpio::GPIO_BUTTON_BOTTOM_LEFT, Buttons::ButtonIds::BUTTON_BOTTOM_LEFT},
    {Buttons::Gpio::GPIO_BUTTON_TOP_RIGHT, Buttons::ButtonIds::BUTTON_TOP_RIGHT},
    {Buttons::Gpio::GPIO_BUTTON_BOTTOM_RIGHT, Buttons::ButtonIds::BUTTON_BOTTOM_RIGHT},
    {Buttons::Gpio::GPIO_PADDLE_BOTTOM_LEFT, Buttons::ButtonIds::PADDLE_BOTTOM_LEFT},
    {Buttons::Gpio::GPIO_PADDLE_BOTTOM_RIGHT, Buttons::ButtonIds::PADDLE_BOTTOM_RIGHT},
    {Buttons::Gpio::GPIO_PADDLE_TOP_LEFT, Buttons::ButtonIds::PADDLE_TOP_LEFT},
    {Buttons::Gpio::GPIO_PADDLE_TOP_RIGHT, Buttons::ButtonIds::PADDLE_TOP_RIGHT},
};

Buttons::Buttons(QObject *parent) : QObject(parent) {
  // Init GPIO access
  wiringPiSetup();
  mcp23017Setup(100, 0x20); // manettino left + manettino right
  mcp23017Setup(116, 0x27); // manettino center + paddles top + paddles bottom +
                            // buttons top + buttons bottom

  pinMap = QVector<int>();
  pinState = QVector<int>();
  pinStatePrevious = QVector<int>();
  buttonState = QVector<States>();

  buttonAction = -1;
  oldTc = -1;
  oldPump = -1;
  oldMap = -1;
  tc = -1;
  pump = -1;
  map = -1;

  switchTimer = QElapsedTimer();
  switchTimer.start();

  switchIsWrong = false;

  pins = {
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

  for (int i = 0; i < pins.size(); i++) {
    pinMode(pins[i], INPUT);
    pullUpDnControl(pins[i], PUD_UP);

    pinState.append(1);
    pinStatePrevious.append(1);
    buttonState.append(BUTTON_NORMAL);
  }

  // Setup signal/slot mechanism
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(readGpioState()));
  timer->start(30);
}

void Buttons::readGpioState() {
  for (int i = 0; i < pins.size(); i++) {
    pinState[i] = digitalRead(pins.at(i));

    if (pinState.at(i) != pinStatePrevious.at(i)) {
      buttonAction = -1;
      pump = -1;
      map = -1;
      tc = -1;

      switch (buttonState.at(i)) {
      case BUTTON_NORMAL:
        this->buttonState[i] = BUTTON_PRESSED;
        this->buttonAction = BUTTON_PRESSED;
        break;
      case BUTTON_PRESSED:
        this->buttonState[i] = BUTTON_NORMAL;
        this->buttonAction = BUTTON_NORMAL;
        break;
      }

      if (buttonAction == BUTTON_PRESSED) {
        emit buttonPressed(buttonIds[pins[i]]);
      } else {
        emit buttonReleased(buttonIds[pins[i]]);
        emit buttonClicked(buttonIds[pins[i]]);
      }

#ifdef QT_DEBUG
      QMetaEnum metaEnum = QMetaEnum::fromType<Buttons::Gpio>();
      QString name = metaEnum.valueToKey(pins[i]);
      if (name.length() > 0) {
        sDebug("buttons") << pins[i] << name << "changed state to:" << pinState[i];
      } else {
        sDebug("buttons") << pins[i] << "changed state to:" << pinState[i];
      }
#endif

      if (pins[i] >= Gpio::GPIO_MANETTINO_LEFT_START && pins[i] <= Gpio::GPIO_MANETTINO_LEFT_END) {
        this->pump = pins[i] - Gpio::GPIO_MANETTINO_LEFT_START;
      } else if (pins[i] >= Gpio::GPIO_MANETTINO_CENTER_START && pins[i] <= Gpio::GPIO_MANETTINO_CENTER_END) {
        this->map = pins[i] - Gpio::GPIO_MANETTINO_CENTER_START;
      } else if (pins[i] >= Gpio::GPIO_MANETTINO_RIGHT_START && pins[i] <= Gpio::GPIO_MANETTINO_RIGHT_END) {
        this->tc = pins[i] - Gpio::GPIO_MANETTINO_RIGHT_START;
      }

      if ((map != -1 && map != oldMap) || (pump != -1 && pump != oldPump) || (tc != -1 && tc != oldTc)) {
        int timeElapsed = switchTimer.restart();

        if (timeElapsed < 15) {
          switchIsWrong = true;
        }

        if (!switchIsWrong) {
          if (map != -1 && map != oldMap) {
            emit mapChanged(map);
            oldMap = map;
          }
          if (pump != -1 && pump != oldPump) {
            emit pumpChanged(pump);
            oldPump = pump;
          }
          if (tc != -1 && tc != oldTc) {
            emit tractionControlChanged(tc);
            oldTc = tc;
          }
        }

        switchIsWrong = false;
      }
    }

    pinStatePrevious[i] = pinState.at(i);
  }
}

bool Buttons::eventFilter(QObject *, QEvent *) {}

Buttons::~Buttons() { delete timer; }
