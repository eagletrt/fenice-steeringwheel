#include "car/das.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"


DAS::DAS(State *parent) : QObject(parent), m_state(parent) {}

DAS::~DAS() { sDebug("das") << "cleanup"; }

void DAS::send_toggle_car_status() {
  quint8 *data = new quint8[sizeof(primary_SET_CAR_STATUS)];
  switch (m_car_status) {
    case CAR_STATUS_IDLE:
      serialize_primary_SET_CAR_STATUS(data, primary_Car_Status_Set_RUN);
      break;
    case CAR_STATUS_SETUP:
      serialize_primary_SET_CAR_STATUS(data, primary_Car_Status_Set_RUN);
      break;
    case CAR_STATUS_RUN:
      serialize_primary_SET_CAR_STATUS(data, primary_Car_Status_Set_IDLE);
      break;
  }
  QByteArray message((const char *)data);
  emit m_state->send_message(CanDevice::Network::PRIMARY, ID_SET_CAR_STATUS, message);
  delete[] data;
}

void DAS::on_button_clicked(int button) {
  if (button == Buttons::Input::BUTTON_START_STOP) {
    send_toggle_car_status();
  }
}
