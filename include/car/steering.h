#ifndef STEERING_H
#define STEERING_H

#include <QObject>
#include <QTimer>

#include "car/interface.h"
#include "global.h"
#include "primary/c/network.h"

class State;

#define STEERING_POLL_TIMER 5000

class Steering : public Interface {
  Q_OBJECT
public:
  S_PROPERTY(float, temperature, 0)
  S_PROPERTY(quint8, map, 0)
  S_PROPERTY(quint8, traction_control, primary_TractionControl_OFF)
  S_PROPERTY(bool, ptt, false)
  S_PROPERTY(QString, build_date_time, "CURRENT BUILD: unavailable")
  S_PROPERTY(QString, ip_addr, "unavailable");
  S_PROPERTY(quint32, canlib_build_hash, 0);

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
  void send_car_status();

private:
  QTimer *m_poll_timer;
  QTimer *m_send_car_status_timer;
  State *m_state;
};

#endif // STEERING_H
