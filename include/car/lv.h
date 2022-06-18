#ifndef LV_H
#define LV_H

#include <QObject>

#include "global.h"

class State;

class LV : public QObject {
  Q_OBJECT
  S_PROPERTY(quint8, current)
  S_PROPERTY(float, voltage_1)
  S_PROPERTY(float, voltage_2)
  S_PROPERTY(float, voltage_3)
  S_PROPERTY(float, voltage_4)
  S_PROPERTY(float, voltage_min)
  S_PROPERTY(quint16, total_voltage)
  S_PROPERTY(float, dcdc_temperature)
  S_PROPERTY(float, battery_temperature)
  S_PROPERTY(quint8, radiators_speed)
  S_PROPERTY(quint8, pumps_speed)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  LV(State *parent = nullptr);
  ~LV();

private:
  State *m_state;
};

#endif // LV_H
