#include "car/ecu.h"

#include "car/state.h"
#include "global.h"

ECU::ECU(State *parent) : QObject(parent), m_state(parent) {}

ECU::~ECU() { sDebug("ecu") << "cleanup"; }
