#include "car/hv.h"

#include "car/state.h"
#include "global.h"

HV::HV(State *parent) : Interface(parent), m_state(parent) {}

HV::~HV() { sDebug("hv") << "cleanup"; }
