#ifndef HV_H
#define HV_H

#include <QObject>

class State;

class HV : public QObject {
  Q_OBJECT
public:
  HV(State *parent = nullptr);
  ~HV();

private:
  State* m_state;

private:
  quint16 m_pack_voltage;
  quint16 m_bus_voltage;
  quint16 m_max_cell_voltage;
  quint16 m_min_cell_voltage;
  quint16 m_current;
  qint16 m_power;
  quint16 m_average_temp;
  quint16 m_max_temp;
  quint16 m_min_temp;
  quint8 m_errors[2];
  quint8 m_warnings[2];
  quint8 m_ts_status;
};

#endif // HV_H
