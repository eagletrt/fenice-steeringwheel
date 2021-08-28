#ifndef BUTTONS_H
#define BUTTONS_H

#include <QElapsedTimer>
#include <QGuiApplication>
#include <QHash>
#include <QTime>
#include <QTimer>
#include <QVector>

class Buttons : public QObject {
  Q_OBJECT
public:
  Buttons(QObject *parent = nullptr);
  ~Buttons();

  enum States {
    BUTTON_NORMAL = 0,
    BUTTON_PRESSED,
  };

  enum Gpio {
    GPIO_BUTTON_START_STOP = 25,

    GPIO_MANETTINO_RIGHT_START = 100,
    GPIO_MANETTINO_RIGHT_END = 107,
    GPIO_MANETTINO_LEFT_START = 108,
    GPIO_MANETTINO_LEFT_END = 115,

    GPIO_PADDLE_BOTTOM_RIGHT = 116,
    GPIO_PADDLE_TOP_RIGHT,
    GPIO_PADDLE_BOTTOM_LEFT,
    GPIO_PADDLE_TOP_LEFT,
    GPIO_BUTTON_BOTTOM_LEFT,
    GPIO_BUTTON_TOP_RIGHT,
    GPIO_BUTTON_TOP_LEFT,
    GPIO_BUTTON_BOTTOM_RIGHT,

    GPIO_MANETTINO_CENTER_START = 124,
    GPIO_MANETTINO_CENTER_END = 131,
  };
  Q_ENUM(Gpio)

  enum Input {
    BUTTON_TOP_LEFT = 0,
    BUTTON_BOTTOM_LEFT,
    BUTTON_TOP_RIGHT,
    BUTTON_BOTTOM_RIGHT,
    PADDLE_TOP_LEFT,
    PADDLE_BOTTOM_LEFT,
    PADDLE_TOP_RIGHT,
    PADDLE_BOTTOM_RIGHT,
    BUTTON_START_STOP
  };
  Q_ENUM(Input)

protected slots:
  void readGpioState();
  bool eventFilter(QObject *obj, QEvent *event) override;

signals:
  void buttonPressed(int button);
  void buttonReleased(int button);
  void buttonClicked(int button);
  void buttonLongClicked(int button);

  void manettinoLeftChanged(int value);
  void manettinoCenterChanged(int value);
  void manettinoRightChanged(int value);

private:
  QTimer *m_poll_timer;
  QElapsedTimer m_switch_timer;

  int m_button_action;
  int m_manettino_left;
  int m_manettino_left_old;
  int m_manettino_center;
  int m_manettino_center_old;
  int m_manettino_right;
  int m_manettino_right_old;

  QVector<States> m_button_state;
  QVector<QElapsedTimer> m_timers;

  QVector<int> m_button_pins_state;
  QVector<int> m_button_pins_state_old;

  QVector<int> m_manettino_pins_state;
  QVector<int> m_manettino_pins_state_old;

  QVector<int> m_button_pins;
  QVector<int> m_manettino_pins;
};

#endif // BUTTONS_H
