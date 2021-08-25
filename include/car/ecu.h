#ifndef ECU_H
#define ECU_H

#include <QObject>

#include "can/primary.h"
#include "global.h"

class State;

class ECU : public QObject {
  Q_OBJECT
public:
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
