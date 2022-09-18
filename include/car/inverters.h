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
  S_PROPERTY(float,   right_temperature, 0.0f)
  S_PROPERTY(float,   left_temperature, 0.0f)
  
  S_PROPERTY(int32_t, right_errors, 0)
  S_PROPERTY(int32_t, right_status, 0)
  S_PROPERTY(int16_t, right_io_info, 0)
  S_PROPERTY(float,   right_motor_temp, 0.0f)
  S_PROPERTY(float,   right_inverter_temp, 0.0f)
  S_PROPERTY(int32_t, right_speed, 0)

  S_PROPERTY(int32_t, left_errors, 0)
  S_PROPERTY(int32_t, left_status, 0)
  S_PROPERTY(int16_t, left_io_info, 0)
  S_PROPERTY(float,   left_motor_temp, 0.0f)
  S_PROPERTY(float,   left_inverter_temp, 0.0f)
  S_PROPERTY(int32_t, left_speed, 0)
public:
  Inverters(State *parent = nullptr);
  ~Inverters();

private:
  State *m_state;
};

#endif // INVERTERS_H
