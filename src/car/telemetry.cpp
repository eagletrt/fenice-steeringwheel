#include "car/telemetry.h"

#include "primary/c/ids.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

Telemetry::Telemetry(State *parent) : QObject(parent), m_state(parent) {}

Telemetry::~Telemetry() { sDebug("telemetry") << "cleanup"; }

void Telemetry::send_status(primary_Toggle status) {
  quint8 *data = new quint8[primary_SET_TLM_STATUS_SIZE];
  primary_serialize_SET_TLM_STATUS(data, 0, 0, (primary_RaceType)0, status);
  QByteArray message((const char *)data, primary_SET_TLM_STATUS_SIZE);

  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_id_SET_TLM_STATUS, message);

  delete[] data;
}

void Telemetry::send_marker() {
  QByteArray message; // empty _._
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_id_MARKER, message);
}

void Telemetry::button_clicked(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == primary_Toggle_ON) {
      emit m_state->show_popup("MARKER");
      send_marker();
    }
  }
}

void Telemetry::button_long_clicked(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == primary_Toggle_OFF) {
      send_status(primary_Toggle_ON);
    } else {
      send_status(primary_Toggle_OFF);
    }
  }
}
