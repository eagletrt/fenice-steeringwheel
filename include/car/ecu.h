#ifndef ECU_H
#define ECU_H

#include <QObject>

class ECU : public QObject {
  Q_OBJECT
public:
  ECU(QObject *parent = nullptr);
  ~ECU();

private:
};

#endif // ECU_H
