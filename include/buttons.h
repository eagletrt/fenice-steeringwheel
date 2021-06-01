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
    BUTTON_START_STOP = 25,

    MANETTINO_RIGHT_START = 100,
    MANETTINO_RIGHT_END = 107,
    MANETTINO_LEFT_START = 108,
    MANETTINO_LEFT_END = 115,

    PADDLE_BOTTOM_RIGHT = 116,
    PADDLE_TOP_RIGHT,
    PADDLE_BOTTOM_LEFT,
    PADDLE_TOP_LEFT,
    BUTTON_BOTTOM_LEFT,
    BUTTON_TOP_RIGHT,
    BUTTON_TOP_LEFT,
    BUTTON_BOTTOM_RIGHT,

    MANETTINO_CENTER_START = 124,
    MANETTINO_CENTER_END = 131,
  };
  Q_ENUM(Gpio)

  const QHash<int, int> buttonIds = QHash<int, int>{
      {Gpio::BUTTON_TOP_LEFT, 0},     {Gpio::BUTTON_BOTTOM_LEFT, 1},
      {Gpio::BUTTON_BOTTOM_RIGHT, 2}, {Gpio::BUTTON_TOP_RIGHT, 3},
      {Gpio::PADDLE_BOTTOM_LEFT, 4},  {Gpio::PADDLE_BOTTOM_RIGHT, 5},
      {Gpio::PADDLE_TOP_LEFT, 6},     {Gpio::PADDLE_TOP_RIGHT, 7},
  };

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
