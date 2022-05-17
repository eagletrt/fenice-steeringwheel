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

  S_PROPERTY(CarStatus, car_status, DAS::CarStatus::CAR_STATUS_IDLE)
  S_PROPERTY(InverterStatus, inverter_l, DAS::InverterStatus::INVERTER_STATUS_OFF)
  S_PROPERTY(InverterStatus, inverter_r, DAS::InverterStatus::INVERTER_STATUS_OFF)
  S_PROPERTY(qint32, left_speed_rads, 0)
  S_PROPERTY(qint32, right_speed_rads, 0)
  S_PROPERTY(float, speed, 100.0f)
  S_PROPERTY(quint16, encoder_r, 0)
  S_PROPERTY(quint16, encoder_l, 0)
  S_PROPERTY(quint8, version_component, 0)
  S_PROPERTY(quint8, version_cancicd, 0)
public:
  DAS(State *parent = nullptr);
  ~DAS();

protected slots:
  void send_toggle_car_status();

public slots:
  void button_clicked(int button);

private:
  State *m_state;
};

#endif // DAS_H
