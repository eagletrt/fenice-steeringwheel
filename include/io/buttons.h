#ifndef BUTTONS_H
#define BUTTONS_H

#include <QElapsedTimer>
#include <QGuiApplication>
#include <QHash>
#include <QTime>
#include <QTimer>
#include <QVector>

#define LONG_PRESS 500
#define MANETTINO_STATE_UPDATE 500
#define MANETTINO_DEBOUNCE 50

class Buttons : public QObject {
  Q_OBJECT
public:
  Buttons(QObject *parent = nullptr);
  ~Buttons();

  enum States {
    BUTTON_NORMAL = 0,
    BUTTON_PRESSED,
  };

  enum Input {
    BUTTON_TOP_LEFT = 0,
    BUTTON_BOTTOM_LEFT,
    BUTTON_TOP_RIGHT,
    BUTTON_BOTTOM_RIGHT,
    PADDLE_TOP_LEFT,
    PADDLE_BOTTOM_LEFT,
    PADDLE_TOP_RIGHT,
    PADDLE_BOTTOM_RIGHT,
    BUTTON_START_STOP,
    BUTTONS_LENGTH
  };
  Q_ENUM(Input)

  enum Gpio {
    GPIO_BUTTON_START_STOP = 25,

    GPIO_MANETTINO_RIGHT_START = 100,
    GPIO_MANETTINO_RIGHT_END = 107,
    GPIO_MANETTINO_LEFT_START = 108,
    GPIO_MANETTINO_LEFT_END = 115,

    GPIO_BUTTON_TOP_LEFT = 116,
    GPIO_PADDLE_TOP_LEFT,
    GPIO_PADDLE_BOTTOM_LEFT,
    GPIO_PADDLE_BOTTOM_RIGHT,
    GPIO_BUTTON_TOP_RIGHT,
    GPIO_BUTTON_BOTTOM_RIGHT,
    GPIO_PADDLE_TOP_RIGHT,
    GPIO_BUTTON_BOTTOM_LEFT,

    GPIO_MANETTINO_CENTER_START = 124,
    GPIO_MANETTINO_CENTER_END = 131,
  };

protected slots:
  void read_gpio_state();
  bool eventFilter(QObject *obj, QEvent *event) override;

signals:
  void button_pressed(int button);
  void button_released(int button);
  void button_long_pressed(int button);
  void button_clicked(int button);
  void button_long_clicked(int button);

  void manettino_left_changed(int value);
  void manettino_left(int value);

  void manettino_center_changed(int value);
  void manettino_center(int value);

  void manettino_right_changed(int value);
  void manettino_right(int value);

private:
  QTimer *m_poll_timer;
  QElapsedTimer m_switch_timer;

  quint8 m_button_action;

  quint8 m_manettino_left = 0;
  quint8 m_manettino_left_state = 0;
  quint8 m_manettino_left_old = 0;

  quint8 m_manettino_center = 0;
  quint8 m_manettino_center_state = 0;
  quint8 m_manettino_center_old = 0;

  quint8 m_manettino_right = 0;
  quint8 m_manettino_right_state = 0;
  quint8 m_manettino_right_old = 0;

  QVector<States> m_button_state;
  QElapsedTimer m_manettino_elapsed_timer;
  QElapsedTimer m_pressed_elapsed_timers[BUTTONS_LENGTH];
  QTimer *m_long_pressed_timers[BUTTONS_LENGTH];

  QVector<quint8> m_button_pins_state;
  QVector<quint8> m_button_pins_state_old;

  QVector<quint8> m_manettino_pins_state;
  QVector<quint8> m_manettino_pins_state_old;

  QVector<quint8> m_button_pins;
  QVector<quint8> m_manettino_pins;
};

#endif // BUTTONS_H
