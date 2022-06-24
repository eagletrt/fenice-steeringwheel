#include "car/lv.h"

#include "car/state.h"

LV::LV(State *parent) : Interface(parent), m_state(parent) {}

LV::~LV() { sDebug("lv") << "cleanup"; }

void LV::send_cooling_status(LV::CoolingStatus status) {
  primary_Cooling pumps = primary_Cooling_SET_OFF, radiators = primary_Cooling_SET_OFF;
  switch (status) {
  case LV::CoolingStatus::OFF: {
    pumps = primary_Cooling_SET_OFF;
    radiators = primary_Cooling_SET_OFF;
    break;
  }
  case LV::CoolingStatus::PUMPS: {
    pumps = primary_Cooling_SET_MAX;
    radiators = primary_Cooling_SET_OFF;
    break;
  }
  case LV::CoolingStatus::ALL: {
    pumps = primary_Cooling_SET_MAX;
    radiators = primary_Cooling_SET_MAX;
    break;
  }
  }
  quint8 *data = new quint8[primary_SIZE_SET_PUMPS_SPEED];
  primary_serialize_SET_PUMPS_SPEED(data, pumps);
  QByteArray pumps_message((const char *)data, primary_SIZE_SET_TLM_STATUS);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_PUMPS_SPEED, pumps_message);
  delete[] data;

  data = new quint8[primary_SIZE_SET_RADIATOR_SPEED];
  primary_serialize_SET_RADIATOR_SPEED(data, radiators);
  QByteArray radiators_message((const char *)data, primary_SIZE_SET_RADIATOR_SPEED);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_RADIATOR_SPEED, radiators_message);
  delete[] data;
}

void LV::manettino_center_changed(int value) {
  if (value <= LV::CoolingStatus::ALL) {
    send_cooling_status((LV::CoolingStatus)value);
  }
}
