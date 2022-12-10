#ifndef LV_H
#define LV_H

#include <QObject>

#include "car/interface.h"
#include "global.h"

class State;

class LV : public Interface {
  Q_OBJECT
public:
  S_PROPERTY(float, current, 0)
  S_PROPERTY(float, voltage_1, 0)
  S_PROPERTY(float, voltage_2, 0)
  S_PROPERTY(float, voltage_3, 0)
  S_PROPERTY(float, voltage_4, 0)
  S_PROPERTY(float, voltage_min, 0)
  S_PROPERTY(float, voltage_max, 0)
  S_PROPERTY(quint16, total_voltage, 0)
  S_PROPERTY(float, dcdc_temperature, 0)
  S_PROPERTY(float, battery_temperature, 0)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint32, version_cancicd, 0)
  S_PROPERTY(quint32, errors, 0);
  S_PROPERTY(QString, canlib_build_time, "unavailable")

public:
  LV(State *parent = nullptr);
  ~LV();

public slots:

private:
  State *m_state;
};

#endif // LV_H
