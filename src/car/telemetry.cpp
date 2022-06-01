#include "car/telemetry.h"

#include "primary/c/ids.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

Telemetry::Telemetry(State *parent) : QObject(parent), m_state(parent) {}

Telemetry::~Telemetry() { sDebug("telemetry") << "cleanup"; }

void Telemetry::send_status(primary_Toggle status, quint8 pilot, primary_RaceType race, quint8 circuit) {
  quint8 *data = new quint8[primary_TLM_STATUS_SIZE];
  primary_serialize_TLM_STATUS(data, pilot, circuit, race, status);
  QByteArray message((const char *)data);

  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_id_TLM_STATUS, message);

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
      set_status(primary_Toggle_ON);
    } else {
      set_status(primary_Toggle_OFF);
    }
  }
}
