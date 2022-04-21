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
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  Telemetry(State *parent = nullptr);
  ~Telemetry();

protected slots:
  void send_status(TlmStatus status, quint8 pilot, Race race, quint8 circuit);

public slots:
  void on_button_clicked(int button);
  void on_button_long_clicked(int button);

private:
  State *m_state;
};

#endif // TELEMETRY_H
