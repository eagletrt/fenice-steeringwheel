#include "car/hv.h"

#include "global.h"
#include "car/state.h"

HV::HV(State* parent) : QObject(parent), m_state(parent) {}

HV::~HV() {
  sDebug("hv") << "cleanup";
}