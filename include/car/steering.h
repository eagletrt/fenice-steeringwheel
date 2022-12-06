#ifndef STEERING_H
#define STEERING_H

#include <QObject>
#include <QTimer>
#include <ctime>

#include "car/interface.h"
#include "global.h"
#include "primary/c/network.h"

class State;

#define STEERING_POLL_TIMER 5000

class Steering : public Interface {
  Q_OBJECT
public:
  S_PROPERTY(float, temperature, 0)
  S_PROPERTY(bool, ptt, false)
  S_PROPERTY(QString, build_date_time, "unavailable")
  S_PROPERTY(QString, ip_addr, "unavailable")
  S_PROPERTY(quint32, canlib_build_hash, 0)
  S_PROPERTY(QString, canlib_build_time, "unavailable")
  S_PROPERTY(qint32, power_map_index, 2)
  S_PROPERTY(qint32, slip_control_index, 0)
  S_PROPERTY(qint32, torque_vectoring_index, 0)
  S_PROPERTY(QList<qint32>, pm_values)
  S_PROPERTY(QList<qint32>, tv_values)
  S_PROPERTY(QList<qint32>, sc_values)

public:
  Steering(State *parent = nullptr);
  ~Steering();

protected slots:
  void poll();

public slots:
  void button_pressed(int button);
  void button_released(int button);
  void send_steer_status();
  void send_set_torque_vectoring(int);
  void send_set_slip_control(int);
  void send_set_power_map(int);

private:
  QTimer *m_poll_timer;
  QTimer *m_send_steer_status_timer;
  State *m_state;
};

#endif // STEERING_H
