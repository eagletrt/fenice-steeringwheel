#ifndef STEERING_H
#define STEERING_H

#include <QObject>
#include <QTimer>

#include "global.h"

class State;

#define STEERING_POLL_TIMER 5000

class Steering : public QObject {
  Q_OBJECT
public:
  enum TCStatus {
    TC_STATUS_OFF,
    TC_STATUS_SLIP,
    TC_STATUS_TORQUE,
    TC_STATUS_SLIP_AND_TORQUE,
  };
  Q_ENUM(TCStatus)

  S_PROPERTY(float, temperature, m_temperature, Temperature, 0)
  S_PROPERTY(quint8, map, m_map, Map, 0)
  S_PROPERTY(TCStatus, tractionControl, m_traction_control, TractionControl, TCStatus::TC_STATUS_OFF)
  S_PROPERTY(bool, ptt, m_ptt, Ptt, false)
public:
  Steering(State *parent = nullptr);
  ~Steering();

protected slots:
  void poll();

public slots:
  void onButtonPressed(int button);
  void onButtonReleased(int button);
  void onManettinoLeftChanged(int value);
  void onManettinoRightChanged(int value);

private:
  QTimer *m_poll_timer;
  State *m_state;
};

#endif // STEERING_H
