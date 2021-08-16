#ifndef HV_H
#define HV_H

#include <QObject>

class HV : public QObject {
  Q_OBJECT
public:
  HV(QObject *parent = nullptr);
  ~HV();

private:
};

#endif // HV_H
