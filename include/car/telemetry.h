#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>
#include <QVector>

#include "global.h"
#include "primary/c/network.h"

class State;

class Telemetry : public QObject {
  Q_OBJECT

public:
  S_PROPERTY(primary_Toggle, status, primary_Toggle_OFF)
  S_PROPERTY(quint8, pilot, 0)
  S_PROPERTY(primary_RaceType, race, primary_RaceType_AUTOCROSS)
  S_PROPERTY(quint8, circuit, 0)
  S_PROPERTY(float, latitude, 0)
  S_PROPERTY(float, longitude, 0)
  S_PROPERTY(quint16, gps_speed, 0)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  Telemetry(State *parent = nullptr);
  ~Telemetry();

private:
  void send_status(primary_Toggle status, quint8 pilot, primary_RaceType race, quint8 circuit);
  void send_marker();

public slots:
  void button_clicked(int button);
  void button_long_clicked(int button);

private:
  State *m_state;
};

#endif // TELEMETRY_H
