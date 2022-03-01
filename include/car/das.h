#ifndef DAS_H
#define DAS_H

#include <QObject>

#include "can/primary.h"
#include "global.h"

class State;

class DAS : public QObject {
  Q_OBJECT
public:
  enum CarStatus {
    CAR_STATUS_IDLE /*= Primary_Car_Status_IDLE*/,
    CAR_STATUS_SETUP /*= Primary_Car_Status_SETUP*/,
    CAR_STATUS_RUN /*= Primary_Car_Status_RUN*/,
  };
  Q_ENUM(CarStatus);

  enum InverterStatus {
    INVERTER_STATUS_OFF /*= Primary_Inverter_Status_OFF*/,
    INVERTER_STATUS_IDLE /*= Primary_Inverter_Status_IDLE*/,
    INVERTER_STATUS_ON /*= Primary_Inverter_Status_ON*/,
  };
  Q_ENUM(InverterStatus);

  S_PROPERTY(CarStatus, carStatus, m_car_status, CarStatus, DAS::CarStatus::CAR_STATUS_IDLE)
  S_PROPERTY(InverterStatus, inverterStatusLeft, m_inverter_l, InverterStatusLeft,
             DAS::InverterStatus::INVERTER_STATUS_OFF)
  S_PROPERTY(InverterStatus, inverterStatusRight, m_inverter_r, InverterStatusRight,
             DAS::InverterStatus::INVERTER_STATUS_OFF)
  S_PROPERTY(qint32, leftSpeedRads, m_left_speed_rads, LeftSpeedRads, 0)
  S_PROPERTY(qint32, rightSpeedRads, m_right_speed_rads, RightSpeedRads, 0)
  S_PROPERTY(float, speed, m_speed, Speed, 0)
  S_PROPERTY(quint16, encoderR, m_encoder_r, EncoderR, 0)
  S_PROPERTY(quint8, dasVersionComponent, dasVersionComponent_r, DasVersionComponent, 0)
  S_PROPERTY(quint8, dasVersionCancicd, dasVersionCancicd_r, DasVersionCancicd, 0)
  S_PROPERTY(quint8, hvVersionComponent, hvVersionComponent_r, HvVersionComponent, 0)
  S_PROPERTY(quint8, hvVersionCancicd, hvVersionCancicd_r, HvVersionCancicd, 0)
  S_PROPERTY(quint8, lvVersionComponent, lvVersionComponent_r, LvVersionComponent, 0)
  S_PROPERTY(quint8, lvVersionCancicd, lvVersionCancicd_r, LvVersionCancicd, 0)
  S_PROPERTY(quint8, tlmVersionComponent, tlmVersionComponent_r, TlmVersionComponent, 0)
  S_PROPERTY(quint8, tlmVersionCancicd, tlmVersionCancicd_r, TlmVersionCancicd, 0)
public:
  DAS(State *parent = nullptr);
  ~DAS();

protected slots:
  void sendToggleCarStatus();

public slots:
  void onButtonClicked(int button);

private:
  State *m_state;
};

#endif // DAS_H
