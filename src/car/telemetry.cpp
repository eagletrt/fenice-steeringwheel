#include "car/telemetry.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

Telemetry::Telemetry(State *parent) : QObject(parent), m_state(parent) {}

Telemetry::~Telemetry() { sDebug("telemetry") << "cleanup"; }

void Telemetry::send_status(TlmStatus status, quint8 pilot, Race race, quint8 circuit) {
  quint8 *data = new quint8[sizeof(primary_SET_TLM_STATUS)];
  serialize_primary_SET_TLM_STATUS(data, (primary_Tlm_Status_Set)status, (primary_Race_Type)race, pilot, circuit);
  QByteArray message((const char *)data);

  emit m_state->send_message(CanDevice::Network::PRIMARY, ID_TLM_STATUS, message);

  delete[] data;
}

void Telemetry::send_marker() {
  QByteArray message; // empty _._
  emit m_state->send_message(CanDevice::Network::PRIMARY, ID_MARKER, message);
}

void Telemetry::button_clicked(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == TlmStatus::TLM_STATUS_ON) {
      emit m_state->show_popup("MARKER");
      send_marker();
    }
  }
}

void Telemetry::button_long_clicked(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == TlmStatus::TLM_STATUS_OFF) {
      set_status(TlmStatus::TLM_STATUS_ON);
    } else {
      set_status(TlmStatus::TLM_STATUS_OFF);
    }
  }
}
