#ifndef STEERING_H
#define STEERING_H

#include <QObject>
#include <QTimer>

#include "global.h"

class State;

#define STEERING_POLL_TIMER 5000

class Steering : public QObject {
  Q_OBJECT
  S_PROPERTY(float, temperature, m_temperature, Temperature, 0)
  S_PROPERTY(quint8, map, m_map, Map, 0)
  S_PROPERTY(quint8, pump, m_pump, Pump, 0)
  S_PROPERTY(quint8, tractionControl, m_traction_control, TractionControl, 0)
public:
  Steering(State *parent = nullptr);
  ~Steering();

protected slots:
  void poll();

private:
  QTimer *m_poll_timer;
  State *m_state;
};

#endif // STEERING_H
