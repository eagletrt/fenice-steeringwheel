#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>

class State;

class Telemetry : public QObject {
  Q_OBJECT
public:
  Telemetry(State *parent = nullptr);
  ~Telemetry();

private:
  State *m_state;
};

#endif // TELEMETRY_H
