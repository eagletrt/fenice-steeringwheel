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
#define POWER_MAP_VALUES                                                                                               \
  { -2, 1, 2, 3, 4, 5, 8, 10 }
#define TORQUE_VECTORING_VALUES                                                                                        \
  { 0, 1, 2, 3, 4, 5, 6, 10 }
#define SLIP_CONTROL_VALUES                                                                                            \
  { 0, 1, 2, 3, 4, 5, 6, 10 }
#define N_MANETTINI 8

class Steering : public Interface {
  Q_OBJECT
public:
  S_PROPERTY(float, temperature, 0)
  S_PROPERTY(bool, ptt, false)
  S_PROPERTY(QString, build_date_time, "unavailable")
  S_PROPERTY(QString, ip_addr, "unavailable")
  S_PROPERTY(quint32, canlib_build_hash, 0)
  S_PROPERTY(QString, canlib_build_time, "unavailable")
  S_PROPERTY(qint32, power_map_index, 1)
  S_PROPERTY(qint32, slip_control_index, 0)
  S_PROPERTY(qint32, torque_vectoring_index, 0)
  S_PROPERTY(QList<qint32>, pm_values)
  S_PROPERTY(QList<qint32>, tv_values)
  S_PROPERTY(QList<qint32>, sc_values)
  S_PROPERTY(bool, debug_mode, false)

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
  void send_pump_speed(int);
  void send_radiators_speed(int);
  void manettino_left_changed(int);
  void manettino_right_changed(int);
  void manettino_center_changed(int);

private:
  QTimer *m_poll_timer;
  QTimer *m_send_steer_status_timer;
  State *m_state;
};

#endif // STEERING_H
