#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>
#include <QVector>

#include "car/interface.h"
#include "global.h"
#include "primary/c/network.h"

class State;

class Telemetry : public Interface {
  Q_OBJECT

public:
  S_PROPERTY(primary_Toggle, status, primary_Toggle_OFF)
  S_PROPERTY(float, latitude, 0)
  S_PROPERTY(float, longitude, 0)
  S_PROPERTY(quint16, gps_speed, 0)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint32, version_cancicd, 0)
  S_PROPERTY(QString, canlib_build_time, "unavailable")
public:
  Telemetry(State *parent = nullptr);
  ~Telemetry();

private:
  void send_status(primary_Toggle status);
  void send_marker();

public slots:
  void button_clicked(int button);
  void button_long_pressed(int button);

private:
  State *m_state;
};

#endif // TELEMETRY_H
