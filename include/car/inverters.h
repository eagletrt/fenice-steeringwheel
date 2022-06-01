#ifndef INVERTERS_H
#define INVERTERS_H

#include <QObject>

#include "global.h"
#include "primary/c/network.h"

class State;

class Inverters : public QObject {
  Q_OBJECT
public:
  S_PROPERTY(float, right_temperature, 0)
  S_PROPERTY(float, left_temperature, 0)
public:
  Inverters(State *parent = nullptr);
  ~Inverters();

private:
  State *m_state;
};

#endif // INVERTERS_H
