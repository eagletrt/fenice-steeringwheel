#include "car/telemetry.h"

#include "car/state.h"
#include "global.h"

Telemetry::Telemetry(State *parent) : QObject(parent), m_state(parent) {
  m_pilots = {Pilot(0, "Pilotapazzo"), Pilot(1, "Iron512"), Pilot(2, "Pippogas"), Pilot(3, "Nicolareds"),
              Pilot(4, "Mirco")};
  m_races = {Race(0, "Acceleration"), Race(1, "Skippad"), Race(2, "Endurance"), Race(3, "Brake")};
  m_circuits = {
      Circuit(0, "Demo", "qrc:/qml/img/racetracks/demo.png"),
      Circuit(1, "Inverted", "qrc:/qml/img/racetracks/demo_rot.png"),
  };

  connect(this, &Telemetry::pilotChanged, this, &Telemetry::sendStatus);
  connect(this, &Telemetry::circuitChanged, this, &Telemetry::sendStatus);
  connect(this, &Telemetry::raceChanged, this, &Telemetry::sendStatus);
  connect(this, &Telemetry::statusChanged, this, &Telemetry::sendStatus);
}

Telemetry::~Telemetry() { sDebug("telemetry") << "cleanup"; }

void Telemetry::sendStatus() {
  quint8 *data = new quint8[sizeof(Primary_SET_TLM_STATUS)];
  serialize_Primary_SET_TLM_STATUS(data, (Primary_Tlm_Status)m_status, (Primary_Race_Type)m_race, m_pilot, m_circuit);
  QByteArray message((const char *)data);
  emit m_state->sendMessage(CanDevice::Network::PRIMARY, ID_TLM_STATUS, message);
  delete[] data;
}