#ifndef STEERING_H
#define STEERING_H

#include <QObject>
#include <QTimer>

#include "global.h"

class State;

#define STEERING_POLL_TIMER 5000

class Steering : public QObject {
  Q_OBJECT
  S_PROPERTY(float, temperature, m_temperature, Temperature)
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
