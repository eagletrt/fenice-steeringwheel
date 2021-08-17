#ifndef ECU_H
#define ECU_H

#include <QObject>

class State;

class ECU : public QObject {
  Q_OBJECT
public:
  ECU(State *parent = nullptr);
  ~ECU();

private:
  State* m_state;

private:
  quint8 m_tlm_status;
  quint8 m_race_type;
  quint8 m_driver;
  quint8 m_circuit;
  quint8 m_car_status;
  quint8 m_inverter_l;
  quint8 m_inverter_r;
};

#endif // ECU_H
