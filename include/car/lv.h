#ifndef LV_H
#define LV_H

#include <QObject>

#include "global.h"

class State;

class LV : public QObject {
  Q_OBJECT
  S_PROPERTY(quint8, current)
  S_PROPERTY(quint8, voltage_1)
  S_PROPERTY(quint8, voltage_2)
  S_PROPERTY(quint8, voltage_3)
  S_PROPERTY(quint8, voltage_4)
  S_PROPERTY(quint16, total_voltage)
  S_PROPERTY(quint8, dcdc_temperature)
  S_PROPERTY(quint16, battery_temperature)
  S_PROPERTY(quint8, hv_fan_speed)
  S_PROPERTY(quint8, lv_fan_speed)
  S_PROPERTY(quint8, pump_speed)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  LV(State *parent = nullptr);
  ~LV();

private:
  State *m_state;
};

#endif // LV_H
