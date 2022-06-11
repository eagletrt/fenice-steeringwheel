#include "car/das.h"

#include "primary/c/ids.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

DAS::DAS(State *parent) : QObject(parent), m_state(parent) {}

DAS::~DAS() { sDebug("das") << "cleanup"; }

void DAS::send_toggle_car_status() {
  quint8 *data = new quint8[primary_SET_CAR_STATUS_SIZE];
  switch (m_car_status) {
  case primary_CarStatus_IDLE:
    primary_serialize_SET_CAR_STATUS(data, primary_SetCarStatus_RUN);
    break;
  case primary_CarStatus_SETUP:
    primary_serialize_SET_CAR_STATUS(data, primary_SetCarStatus_RUN);
    break;
  case primary_CarStatus_RUN:
    primary_serialize_SET_CAR_STATUS(data, primary_SetCarStatus_IDLE);
    break;
  }
  QByteArray message((const char *)data);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_id_SET_CAR_STATUS, message);
  delete[] data;
}

void DAS::send_set_pedal_range(quint8 pedal, quint8 bound) {
  quint8 *data = new quint8[primary_SET_PEDALS_RANGE_SIZE];
  primary_serialize_SET_PEDALS_RANGE(data, (primary_Bound)bound, (primary_Pedal)pedal);
  QByteArray message((const char *)data);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_id_SET_PEDALS_RANGE, message);
  delete[] data;
}

void DAS::send_set_steering_angle_range(quint8 bound) {
  quint8 *data = new quint8[primary_SET_STEERING_ANGLE_RANGE_SIZE];
  primary_serialize_SET_STEERING_ANGLE_RANGE(data, (primary_Bound)bound);
  QByteArray message((const char *)data);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_id_SET_STEERING_ANGLE_RANGE, message);
  delete[] data;
}

void DAS::button_clicked(int button) {
  if (button == Buttons::Input::BUTTON_START_STOP) {
    send_toggle_car_status();
  }
}
