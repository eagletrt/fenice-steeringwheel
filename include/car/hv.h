#ifndef HV_H
#define HV_H

#include <QObject>

#include "car/interface.h"
#include "global.h"
#include "primary/c/network.h"

class State;

class HV : public Interface {
  Q_OBJECT
public:
  S_PROPERTY(float, pack_voltage, 0)
  S_PROPERTY(quint16, bus_voltage, 0)
  S_PROPERTY(float, max_cell_voltage, 0)
  S_PROPERTY(float, min_cell_voltage, 0)
  S_PROPERTY(quint16, current, 0)
  S_PROPERTY(qint16, power, 0)
  S_PROPERTY(float, average_temperature, 0)
  S_PROPERTY(float, max_temperature, 0)
  S_PROPERTY(float, min_temperature, 0)
  S_PROPERTY(quint16, errors, 0)
  S_PROPERTY(quint32, feedbacks, 0)
  S_PROPERTY(quint16, warnings, 0)
  S_PROPERTY(primary_TsStatus, ts_status, primary_TsStatus_OFF)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  HV(State *parent = nullptr);
  ~HV();

private:
  State *m_state;
};

#endif // HV_H
