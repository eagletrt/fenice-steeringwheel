#ifndef PEDALS_H
#define PEDALS_H

#include <QObject>

class State;

class Pedals : public QObject {
  Q_OBJECT
public:
  Pedals(State *parent = nullptr);
  ~Pedals();

private:
  State *m_state;
};

#endif // PEDALS_H
