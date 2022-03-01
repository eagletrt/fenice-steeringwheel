#include "car/das.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"


DAS::DAS(State *parent) : QObject(parent), m_state(parent) {}

DAS::~DAS() { sDebug("das") << "cleanup"; }

void DAS::sendToggleCarStatus() {
  quint8 *data = new quint8[sizeof(primary_SET_CAR_STATUS)];
  // TODO: when DAS will send car_status we should rewrite this below
  serialize_primary_SET_CAR_STATUS(data, primary_Car_Status_Set::primary_Car_Status_Set_RUN);
  QByteArray message((const char *)data);
  emit m_state->sendMessage(CanDevice::Network::PRIMARY, ID_SET_CAR_STATUS, message);
  delete[] data;
}

void DAS::onButtonClicked(int button) {
  if (button == Buttons::Input::BUTTON_START_STOP) {
    sendToggleCarStatus();
  }
}
