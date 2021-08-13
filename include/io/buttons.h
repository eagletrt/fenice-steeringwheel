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
  };
  Q_ENUM(Input)

protected slots:
  void readGpioState();
  bool eventFilter(QObject *obj, QEvent *event) override;

signals:
  void buttonClicked(int button);
  void buttonPressed(int button);
  void buttonReleased(int button);

  void mapChanged(int map);
  void pumpChanged(int pump);
  void tractionControlChanged(int tractionControl);

private:
  QTimer *timer;
  QElapsedTimer switchTimer;

  bool switchIsWrong;

  int buttonAction;
  int map;
  int oldMap;
  int pump;
  int oldPump;
  int tc;
  int oldTc;

  QVector<States> buttonState;

  QVector<int> pinMap;
  QVector<int> pinState;
  QVector<int> pinStatePrevious;
  QVector<int> pins;
};

#endif // BUTTONS_H
