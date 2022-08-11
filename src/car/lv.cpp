#include "car/lv.h"

#include "car/state.h"

LV::LV(State *parent) : Interface(parent), m_state(parent) {}

LV::~LV() { sDebug("lv") << "cleanup"; }

void LV::send_cooling_status(float pumps, float radiators) {
  primary_message_SET_PUMPS_SPEED set_pumps_speed;
  primary_conversion_to_raw_SET_PUMPS_SPEED(&set_pumps_speed, qBound(-1.f, pumps, 1.f));

  primary_message_SET_RADIATOR_SPEED set_radiator_speed;
  primary_conversion_to_raw_SET_RADIATOR_SPEED(&set_radiator_speed, qBound(-1.f, radiators, 1.f));

  quint8 *data = new quint8[primary_SIZE_SET_PUMPS_SPEED];
  primary_serialize_struct_SET_PUMPS_SPEED(data, &set_pumps_speed);
  QByteArray pumps_message((const char *)data, primary_SIZE_SET_PUMPS_SPEED);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_PUMPS_SPEED, pumps_message);
  delete[] data;

  data = new quint8[primary_SIZE_SET_RADIATOR_SPEED];
  primary_serialize_struct_SET_RADIATOR_SPEED(data, &set_radiator_speed);
  QByteArray radiators_message((const char *)data, primary_SIZE_SET_RADIATOR_SPEED);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_RADIATOR_SPEED, radiators_message);
  delete[] data;
}

void LV::manettino_center_changed(int value) {
  switch ((LV::CoolingStatus)value) {
  case LV::CoolingStatus::AUTO:
    return send_cooling_status(-1, -1);
  case LV::CoolingStatus::OFF:
    return send_cooling_status(0, 0);
  case LV::CoolingStatus::PUMPS_025:
    return send_cooling_status(.25, 0);
  case LV::CoolingStatus::PUMPS_050:
    return send_cooling_status(.50, 0);
  case LV::CoolingStatus::PUMPS_100:
    return send_cooling_status(1, 0);
  case LV::CoolingStatus::ALL_025:
    return send_cooling_status(0.25, 0.25);
  case LV::CoolingStatus::ALL_050:
    return send_cooling_status(1, 0.50);
  case LV::CoolingStatus::ALL_100:
    return send_cooling_status(1, 1);
  default:
    break;
  }
}
