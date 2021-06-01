#ifndef DETECT_H
#define DETECT_H

#include <QByteArray>
#include <QCanBus>
#include <QString>
#include <QThread>

class Detect : public QObject {
  Q_OBJECT
  QCanBusDevice *device;
public slots:
  void startDevice();
  void getSerial();
signals:
  void result(int canId, QByteArray canMsg);

public:
  Detect(QCanBusDevice *);
};

#endif // DETECT_H
