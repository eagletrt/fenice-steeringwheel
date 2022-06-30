#include "car/das.h"

#include "primary/c/ids.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

DAS::DAS(State *parent) : Interface(parent), m_state(parent) {}

DAS::~DAS() { sDebug("das") << "cleanup"; }

void DAS::send_toggle_car_status() {
  quint8 *data = new quint8[primary_SIZE_SET_CAR_STATUS];
  switch (m_car_status) {
  case primary_CarStatus_IDLE:
    primary_serialize_SET_CAR_STATUS(data, primary_SetCarStatus_READY);
    break;
  case primary_CarStatus_TS_ON:
    primary_serialize_SET_CAR_STATUS(data, primary_SetCarStatus_DRIVE);
    break;
  default:
    primary_serialize_SET_CAR_STATUS(data, primary_SetCarStatus_IDLE);
    break;
  }
  QByteArray message((const char *)data, primary_SIZE_SET_CAR_STATUS);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_CAR_STATUS, message);
  delete[] data;
}

void DAS::send_set_pedal_range(quint8 pedal, quint8 bound) {
  quint8 *data = new quint8[primary_SIZE_SET_PEDALS_RANGE];
  primary_serialize_SET_PEDALS_RANGE(data, (primary_Bound)bound, (primary_Pedal)pedal);
  QByteArray message((const char *)data, primary_SIZE_SET_PEDALS_RANGE);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_PEDALS_RANGE, message);
  delete[] data;
}

void DAS::send_set_steering_angle_range(quint8 bound) {
  quint8 *data = new quint8[primary_SIZE_SET_STEERING_ANGLE_RANGE];
  primary_serialize_SET_STEERING_ANGLE_RANGE(data, (primary_Bound)bound);
  QByteArray message((const char *)data, primary_SIZE_SET_STEERING_ANGLE_RANGE);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_STEERING_ANGLE_RANGE, message);
  delete[] data;
}

void DAS::button_clicked(int button) {
  if (button == Buttons::Input::BUTTON_START_STOP) {
    send_toggle_car_status();
  }
}
