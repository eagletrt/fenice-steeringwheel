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
    TS_STATUS_OFF = Primary_Ts_Status_OFF,
    TS_STATUS_PRECHARGE = Primary_Ts_Status_PRECHARGE,
    TS_STATUS_ON = Primary_Ts_Status_ON,
    TS_STATUS_FATAL = Primary_Ts_Status_FATAL,
  };
  Q_ENUM(TsStatus)

  S_PROPERTY(quint16, packVoltage, m_pack_voltage, PackVoltage)
  S_PROPERTY(quint16, busVoltage, m_bus_voltage, BusVoltage)
  S_PROPERTY(quint16, maxCellVoltage, m_max_cell_voltage, MaxCellVoltage)
  S_PROPERTY(quint16, minCellVoltage, m_min_cell_voltage, MinCellVoltage)
  S_PROPERTY(quint16, current, m_current, Current)
  S_PROPERTY(qint16, power, m_power, Power)
  S_PROPERTY(quint16, averageTemperature, m_average_temperature, AverageTemperature)
  S_PROPERTY(quint16, maxTemperature, m_max_temperature, MaxTemperature)
  S_PROPERTY(quint16, minTemperature, m_min_temperature, MinTemperature)
  S_PROPERTY(quint16, errors, m_errors, Errors)
  S_PROPERTY(quint16, warnings, m_warnings, Warnings)
  S_PROPERTY(TsStatus, tsStatus, m_ts_status, TsStatus)
public:
  HV(State *parent = nullptr);
  ~HV();

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

private:
  State *m_state;
};

#endif // HV_H
