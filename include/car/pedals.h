#ifndef PEDALS_H
#define PEDALS_H

#include <QObject>

#include "global.h"

class State;

class Pedals : public QObject {
  Q_OBJECT
  S_PROPERTY(float, apps, m_apps, Apps, 0)
  S_PROPERTY(float, steer, m_steer, Steer, 0)
  S_PROPERTY(float, bse, m_bse, Bse, 0)
public:
  Pedals(State *parent = nullptr);
  ~Pedals();

private:
  State *m_state;
};

#endif // PEDALS_H
