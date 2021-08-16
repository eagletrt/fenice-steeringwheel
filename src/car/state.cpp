#include "car/state.h"

#include "steering.h"

#define __STDC_VERSION__ 201112

#include "Primary/c/Primary.h"
#include "Primary/can_config.h"
#include "Primary/ids.h"

#include "Secondary/c/Secondary.h"
#include "Secondary/can_config.h"
#include "Secondary/ids.h"

State::State(QObject *parent) : QObject(parent) {
  m_ecu = new ECU(this);
  m_hv = new HV(this);
  m_lv = new LV(this);
  m_pedals = new Pedals(this);
  m_telemetry = new Telemetry(this);
}

State::~State() {
  sDebug("state") << "cleanup";
  delete m_ecu;
  delete m_hv;
  delete m_lv;
  delete m_pedals;
  delete m_telemetry;
}

void State::handleMessage(const CanDevice *device, int id, const QByteArray &message) {
  return;
}
