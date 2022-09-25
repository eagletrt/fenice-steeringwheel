#ifndef INVERTERS_H
#define INVERTERS_H

#include <QObject>

#include "car/interface.h"
#include "global.h"
#include "primary/c/network.h"

class State;

class Inverters : public Interface {
  Q_OBJECT
public:
  S_PROPERTY(float, right_temperature, 0.0f)
  S_PROPERTY(float, left_temperature, 0.0f)

  S_PROPERTY(qint32, right_errors, 0)
  S_PROPERTY(qint32, right_status, 0)
  S_PROPERTY(qint16, right_io_info, 0)
  S_PROPERTY(float, right_motor_temp, 0.0f)
  S_PROPERTY(float, right_inverter_temp, 0.0f)
  S_PROPERTY(qint32, right_speed, 0)

  S_PROPERTY(qint32, left_errors, 0)
  S_PROPERTY(qint32, left_status, 0)
  S_PROPERTY(qint16, left_io_info, 0)
  S_PROPERTY(float, left_motor_temp, 0.0f)
  S_PROPERTY(float, left_inverter_temp, 0.0f)
  S_PROPERTY(qint32, left_speed, 0)
public:
  Inverters(State *parent = nullptr);
  ~Inverters();

private:
  State *m_state;
};

#endif // INVERTERS_H
