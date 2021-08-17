#ifndef LV_H
#define LV_H

#include <QObject>

class State;

class LV : public QObject {
  Q_OBJECT
public:
  LV(State *parent = nullptr);
  ~LV();

private:
  State* m_state;

private:
  quint8 m_current;
  quint8 m_voltage_1;
  quint8 m_voltage_2;
  quint8 m_voltage_3;
  quint8 m_voltage_4;
  quint16 m_total_voltage;
  quint8 m_dcdc_temperature;
  quint16 m_battery_temperature;
  quint8 m_hv_fan_speed;
  quint8 m_lv_fan_speed;
  quint8 m_pump_speed;
};

#endif // LV_H
