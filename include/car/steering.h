#ifndef STEERING_H
#define STEERING_H

#include <QObject>
#include <QTimer>

class State;

#define STEERING_POLL_TIMER 5000

class Steering : public QObject {
  Q_OBJECT
  Q_PROPERTY(float temperature MEMBER m_temperature NOTIFY temperatureChanged)
public:
  Steering(State *parent = nullptr);
  ~Steering();

signals:
  void temperatureChanged();

protected slots:
  void poll();

private:
  QTimer* m_poll_timer;
  State* m_state;

private:
  float m_temperature;
};

#endif // STEERING_H
