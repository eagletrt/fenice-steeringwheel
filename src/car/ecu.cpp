#include "car/ecu.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

ECU::ECU(State *parent) : QObject(parent), m_state(parent) {}

ECU::~ECU() { sDebug("ecu") << "cleanup"; }

void ECU::sendToggleCarStatus() {
  quint8 *data = new quint8[sizeof(Primary_SET_CAR_STATUS)];
  // TODO: when ECU will send car_status we should rewrite this below
  serialize_Primary_SET_CAR_STATUS(data, Primary_Car_Status_Set::Primary_Car_Status_Set_RUN);
  QByteArray message((const char *)data);
  emit m_state->sendMessage(CanDevice::Network::PRIMARY, ID_SET_CAR_STATUS, message);
  delete[] data;
}

void ECU::onButtonClicked(int button) {
  if (button == Buttons::Input::BUTTON_START_STOP) {
    sendToggleCarStatus();
  }
}
