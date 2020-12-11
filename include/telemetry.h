#ifndef TELEMETRY_H
#define TELEMETRY_H

#define NUM_TESTS 5
#define NUM_DRIVERS 5
#define NUM_RACETRACKS 5

#include <QDebug>

class Telemetry : public QObject {
  Q_OBJECT

public:
  Telemetry();
  void setTest(int);
  void setDriver(int);
  void setRacetrack(int);
  void setAsk(bool);
  void setTelemetryStatus(int);
  void setPopupMessage(QChar, QChar, QString);
  void setSender();
  int getTest() const;
  int getDriver() const;
  int getRacetrack() const;
  bool getAsk();
  int getTelemetryStatus() const;
  QString getPopupMessage() const;
  bool getSender() const;
  void getNUM(int *);

private:
  int test;
  int driver;
  int racetrack;
  bool ask;
  bool sender;
  int telemetryEnStatus;
  QString popup;
};

#endif // TELEMETRY_H
