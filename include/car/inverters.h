#ifndef INVERTERS_H
#define INVERTERS_H

#include <QObject>

#include "can/primary.h"
#include "global.h"

class State;

class Inverters : public QObject {
  Q_OBJECT
public:
  S_PROPERTY(float, rightTemperature, m_right_temperature, RightTemperature, 0)
  S_PROPERTY(float, leftTemperature, m_left_temperature, LeftTemperature, 0)
public:
  Inverters(State *parent = nullptr);
  ~Inverters();

private:
  State *m_state;
};

#endif // INVERTERS_H
