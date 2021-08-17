#include "car/ecu.h"

#include "global.h"
#include "car/state.h"

ECU::ECU(State* parent) : QObject(parent), m_state(parent) {}

ECU::~ECU() {
  sDebug("ecu") << "cleanup";
}

