#ifndef PEDALS_H
#define PEDALS_H

#include <QObject>

class Pedals : public QObject {
  Q_OBJECT
public:
  Pedals(QObject *parent = nullptr);
  ~Pedals();

private:
};

#endif // PEDALS_H
