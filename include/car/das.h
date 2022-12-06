#ifndef DAS_H
#define DAS_H

#include <QObject>

#include "car/interface.h"
#include "global.h"
#include "primary/c/network.h"

class State;

class DAS : public Interface {
  Q_OBJECT
public:
  S_PROPERTY(quint8, car_status, primary_CarStatus_IDLE)
  S_PROPERTY(quint8, inverter_left, primary_InverterStatus_OFF)
  S_PROPERTY(quint8, inverter_right, primary_InverterStatus_OFF)
  S_PROPERTY(qint32, left_speed_rads, 0)
  S_PROPERTY(qint32, right_speed_rads, 0)
  S_PROPERTY(float, speed, 12.21)
  S_PROPERTY(quint16, apps, 0)
  S_PROPERTY(float, bse, 0)
  S_PROPERTY(float, steering_angle, 90) // default position for the steering calibration
  S_PROPERTY(quint16, encoder_right, 0)
  S_PROPERTY(quint16, encoder_left, 0)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint32, version_cancicd, 0)
  S_PROPERTY(quint32, errors, 0)
  S_PROPERTY(QString, canlib_build_time, "unavailable")
public:
  DAS(State *parent = nullptr);
  ~DAS();

protected slots:
  void send_toggle_car_status();
  void send_set_pedal_range(quint8 pedal, quint8 bound);
  void send_set_steering_angle_range(quint8 bound);

public slots:
  void button_clicked(int button);

private:
  State *m_state;
};

#endif // DAS_H
