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

  S_PROPERTY(float, temperature, 0)
  S_PROPERTY(quint8, map, 0)
  S_PROPERTY(TCStatus, traction_control, TCStatus::TC_STATUS_OFF)
  S_PROPERTY(bool, ptt, false)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  Steering(State *parent = nullptr);
  ~Steering();

protected slots:
  void poll();

public slots:
  void button_pressed(int button);
  void button_released(int button);
  void manettino_left_changed(int value);
  void manettino_right_changed(int value);

private:
  QTimer *m_poll_timer;
  State *m_state;
};

#endif // STEERING_H
