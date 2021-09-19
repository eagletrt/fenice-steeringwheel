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
  enum TlmStatus { TLM_STATUS_ON = Primary_Tlm_Status_ON, TLM_STATUS_OFF = Primary_Tlm_Status_OFF };
  Q_ENUM(TlmStatus);

  enum Race { RACE_DEFAULT, RACE_AUTOCROSS, RACE_SKIDPAD, RACE_ENDURANCE, RACE_ACCELERATION };
  Q_ENUM(Race)

  S_PROPERTY(TlmStatus, status, m_status, Status, TlmStatus::TLM_STATUS_OFF)
  S_PROPERTY(quint8, pilot, m_pilot, Pilot, 0)
  S_PROPERTY(Race, race, m_race, Race, Race::RACE_DEFAULT)
  S_PROPERTY(quint8, circuit, m_circuit, Circuit, 0)
public:
  Telemetry(State *parent = nullptr);
  ~Telemetry();

protected slots:
  void sendStatus();

public slots:
  void onButtonClicked(int button);
  void onButtonLongClicked(int button);
  void onManettinoCenterChanged(int value);

private:
  State *m_state;
};

#endif // TELEMETRY_H
