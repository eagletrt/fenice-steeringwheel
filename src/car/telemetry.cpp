#include "car/telemetry.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

Telemetry::Telemetry(State *parent) : QObject(parent), m_state(parent) {
  connect(this, &Telemetry::pilotChanged, this, &Telemetry::sendStatus);
  connect(this, &Telemetry::circuitChanged, this, &Telemetry::sendStatus);
  connect(this, &Telemetry::raceChanged, this, &Telemetry::sendStatus);
  connect(this, &Telemetry::statusChanged, this, &Telemetry::sendStatus);
}

Telemetry::~Telemetry() { sDebug("telemetry") << "cleanup"; }

void Telemetry::sendStatus() {
  quint8 *data = new quint8[sizeof(primary_SET_TLM_STATUS)];
  serialize_primary_SET_TLM_STATUS(data, (primary_Tlm_Status_Set)m_status, (primary_Race_Type)m_race, m_pilot, m_circuit);
  QByteArray message((const char *)data);
  emit m_state->sendMessage(CanDevice::Network::PRIMARY, ID_TLM_STATUS, message);
  delete[] data;
}

void Telemetry::onButtonClicked(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == TlmStatus::TLM_STATUS_ON) {
      emit m_state->showPopup("MARKER");
    }
  }
}

void Telemetry::onButtonLongClicked(int button) {
  if (button == Buttons::Input::BUTTON_TOP_RIGHT) {
    if (m_status == TlmStatus::TLM_STATUS_OFF) {
      setStatus(TlmStatus::TLM_STATUS_ON);
    } else {
      setStatus(TlmStatus::TLM_STATUS_OFF);
    }
  }
}
