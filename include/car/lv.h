#ifndef LV_H
#define LV_H

#include <QObject>

#include "global.h"

class State;

class LV : public QObject {
  Q_OBJECT
  S_PROPERTY(quint8, current, m_current, Current)
  S_PROPERTY(quint8, voltage1, m_voltage_1, Voltage1)
  S_PROPERTY(quint8, voltage2, m_voltage_2, Voltage2)
  S_PROPERTY(quint8, voltage3, m_voltage_3, Voltage3)
  S_PROPERTY(quint8, voltage4, m_voltage_4, Voltage4)
  S_PROPERTY(quint16, totalVoltage, m_total_voltage, TotalVoltage)
  S_PROPERTY(quint8, dcdcTemperature, m_dcdc_temperature, DcdcTemperature)
  S_PROPERTY(quint16, batteryTemperature, m_battery_temperature, BatteryTemperature)
  S_PROPERTY(quint8, hvFanSpeed, m_hv_fan_speed, HvFanSpeed)
  S_PROPERTY(quint8, lvFanSpeed, m_lv_fan_speed, LvFanSpeed)
  S_PROPERTY(quint8, pumpSpeed, m_pump_speed, PumpSpeed)
public:
  LV(State *parent = nullptr);
  ~LV();

private:
  State* m_state;
};

#endif // LV_H
