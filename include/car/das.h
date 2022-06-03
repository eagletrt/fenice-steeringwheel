#ifndef DAS_H
#define DAS_H

#include <QObject>

#include "global.h"
#include "primary/c/network.h"

class State;

class DAS : public QObject {
  Q_OBJECT
public:
  S_PROPERTY(primary_CarStatus, car_status, primary_CarStatus_IDLE)
  S_PROPERTY(primary_InverterStatus, inverter_left, primary_InverterStatus_OFF)
  S_PROPERTY(primary_InverterStatus, inverter_right, primary_InverterStatus_OFF)
  S_PROPERTY(qint32, left_speed_rads, 0)
  S_PROPERTY(qint32, right_speed_rads, 0)
  S_PROPERTY(float, speed, 0)
  S_PROPERTY(quint16, apps, 0)
  S_PROPERTY(float, bse, 0)
  S_PROPERTY(float, steering_angle, 0)
  S_PROPERTY(float, control_left, 0)
  S_PROPERTY(float, control_right, 0)
  S_PROPERTY(quint16, encoder_right, 0)
  S_PROPERTY(quint16, encoder_left, 0)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  DAS(State *parent = nullptr);
  ~DAS();

protected slots:
  void send_toggle_car_status();

public slots:
  void button_clicked(int button);

private:
  State *m_state;
};

#endif // DAS_H
