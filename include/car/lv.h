#ifndef LV_H
#define LV_H

#include <QObject>

#include "car/interface.h"
#include "global.h"

class State;

class LV : public Interface {
  Q_OBJECT
public:
  enum CoolingStatus { AUTO, OFF, PUMPS_025, PUMPS_050, PUMPS_100, ALL_025, ALL_050, ALL_100, LENGTH };

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
  S_PROPERTY(quint8, radiators_speed, 0)
  S_PROPERTY(quint8, pumps_speed, 0)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
  S_PROPERTY(quint32, errors, 0);

public:
  LV(State *parent = nullptr);
  ~LV();
  void send_cooling_status(float pumps, float radiators);

public slots:
  void manettino_center_changed(int value);

private:
  State *m_state;
};

#endif // LV_H
