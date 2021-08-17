#include "car/telemetry.h"

#include "global.h"
#include "car/state.h"

Telemetry::Telemetry(State* parent) : QObject(parent), m_state(parent) {}

Telemetry::~Telemetry() {
  sDebug("telemetry") << "cleanup";
}
