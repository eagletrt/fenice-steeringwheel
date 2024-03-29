#include "car/telemetry.h"

#include "primary/c/ids.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

Telemetry::Telemetry(State *parent) : Interface(parent), m_state(parent) {}

Telemetry::~Telemetry() { sDebug("telemetry") << "cleanup"; }

void Telemetry::send_status(primary_Toggle status) {
  quint8 *data = new quint8[primary_SIZE_SET_TLM_STATUS];
  primary_serialize_SET_TLM_STATUS(data, status);
  QByteArray message((const char *)data, primary_SIZE_SET_TLM_STATUS);

  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_TLM_STATUS, message);

  delete[] data;
}

void Telemetry::send_marker() {
  QByteArray message; // empty _._
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_MARKER, message);
}

void Telemetry::button_clicked(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == primary_Toggle_ON) {
      emit m_state->show_popup("MARKER");
      send_marker();
    }
  }
}

void Telemetry::button_long_pressed(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == primary_Toggle_OFF) {
      send_status(primary_Toggle_ON);
    } else {
      send_status(primary_Toggle_OFF);
    }
  }
}
