#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>
#include <QVector>

#include "can/primary.h"
#include "global.h"

class State;

class Telemetry : public QObject {
  Q_OBJECT

public:
  enum TlmStatus { TLM_STATUS_ON = primary_Tlm_Status_ON, TLM_STATUS_OFF = primary_Tlm_Status_OFF };
  Q_ENUM(TlmStatus);

  enum Race { RACE_DEFAULT, RACE_AUTOCROSS, RACE_SKIDPAD, RACE_ENDURANCE, RACE_ACCELERATION };
  Q_ENUM(Race)

  S_PROPERTY(TlmStatus, status, TlmStatus::TLM_STATUS_OFF)
  S_PROPERTY(quint8, pilot, 0)
  S_PROPERTY(Race, race, Race::RACE_DEFAULT)
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
  void send_status(Telemetry::TlmStatus status, quint8 pilot, Telemetry::Race race, quint8 circuit);
  void send_marker();

public slots:
  void button_clicked(int button);
  void button_long_clicked(int button);

private:
  State *m_state;
};

#endif // TELEMETRY_H
