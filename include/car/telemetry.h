#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>

class Telemetry : public QObject {
  Q_OBJECT
public:
  Telemetry(QObject *parent = nullptr);
  ~Telemetry();

private:
};

#endif // TELEMETRY_H
