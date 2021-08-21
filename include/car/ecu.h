#ifndef ECU_H
#define ECU_H

#include <QObject>

#include "can/primary.h"
#include "global.h"

class State;

class ECU : public QObject {
  Q_OBJECT
public:
  enum TlmStatus { TLM_STATUS_ON = Primary_Tlm_Status_ON, TLM_STATUS_OFF = Primary_Tlm_Status_OFF };
  Q_ENUM(TlmStatus);

  enum RaceType {
    RACE_TYPE_ACCELERATION = Primary_Race_Type_ACCELERATION,
    RACE_TYPE_SKIDPAD = Primary_Race_Type_SKIDPAD,
    RACE_TYPE_AUTOCROSS = Primary_Race_Type_AUTOCROSS,
    RACE_TYPE_ENDURANCE = Primary_Race_Type_ENDURANCE
  };
  Q_ENUM(RaceType);

  enum CarStatus {
    CAR_STATUS_IDLE = Primary_Car_Status_IDLE,
    CAR_STATUS_SETUP = Primary_Car_Status_SETUP,
    CAR_STATUS_RUN = Primary_Car_Status_RUN,
  };
  Q_ENUM(CarStatus);

  enum InverterStatus {
    INVERTER_STATUS_OFF = Primary_Inverter_Status_OFF,
    INVERTER_STATUS_IDLE = Primary_Inverter_Status_IDLE,
    INVERTER_STATUS_ON = Primary_Inverter_Status_ON,
  };
  Q_ENUM(InverterStatus);

  S_PROPERTY(TlmStatus, tlmStatus, m_tlm_status, TlmStatus)
  S_PROPERTY(RaceType, raceType, m_race_type, RaceType)
  S_PROPERTY(quint8, driver, m_driver, Driver)
  S_PROPERTY(quint8, circuit, m_circuit, Circuit)
  S_PROPERTY(CarStatus, carStatus, m_car_status, CarStatus)
  S_PROPERTY(InverterStatus, inverterStatusLeft, m_inverter_l, InverterStatusLeft)
  S_PROPERTY(InverterStatus, inverterStatusRight, m_inverter_r, InverterStatusRight)
public:
  ECU(State *parent = nullptr);
  ~ECU();

private:
  State *m_state;
};

#endif // ECU_H
