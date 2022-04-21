#ifndef HV_H
#define HV_H

#include <QObject>

#include "can/primary.h"
#include "global.h"

class State;

class HV : public QObject {
  Q_OBJECT
public:
  enum TsStatus {
    TS_STATUS_OFF /*= Primary_Ts_Status_OFF*/,
    TS_STATUS_PRECHARGE /*= Primary_Ts_Status_PRECHARGE*/,
    TS_STATUS_ON /*= Primary_Ts_Status_ON*/,
    TS_STATUS_FATAL /*= Primary_Ts_Status_FATAL*/,
  };
  Q_ENUM(TsStatus);

  enum Error {
    LTC_PEC = 0b1,
    CELL_UNDER_VOLTAGE = 0b10,
    CELL_OVER_VOLTAGE = 0b100,
    CELL_OVER_TEMPERATURE = 0b1000,
    OVER_CURRENT = 0b10000,
    ADC_INIT = 0b100000,
    ADC_TIMEOUT = 0b1000000,
    INT_VOLTAGE_MISMATCH = 0b10000000,
    FEEDBACK_HARD = 0b100000000,
    FEEDBACK_SOFT = 0b1000000000
  };
  Q_ENUM(Error);

  S_PROPERTY(float, pack_voltage, 0)
  S_PROPERTY(quint16, bus_voltage, 0)
  S_PROPERTY(quint16, max_cell_voltage, 0)
  S_PROPERTY(quint16, min_cell_voltage, 0)
  S_PROPERTY(quint16, current, 0)
  S_PROPERTY(qint16, power, 0)
  S_PROPERTY(quint16, average_temperature, 0)
  S_PROPERTY(quint16, max_temperature, 0)
  S_PROPERTY(quint16, min_temperature, 0)
  S_PROPERTY(quint16, errors, 0)
  S_PROPERTY(quint16, warnings, 0)
  S_PROPERTY(TsStatus, ts_status, TsStatus::TS_STATUS_OFF)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  HV(State *parent = nullptr);
  ~HV();

private:
  State *m_state;
};

#endif // HV_H
