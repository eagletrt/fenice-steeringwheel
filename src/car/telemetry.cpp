#include "car/telemetry.h"

#include "car/state.h"
#include "global.h"

Telemetry::Telemetry(State *parent) : QObject(parent), m_state(parent) {}

Telemetry::~Telemetry() { sDebug("telemetry") << "cleanup"; }
