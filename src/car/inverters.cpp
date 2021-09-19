#include "car/inverters.h"

#include "car/state.h"
#include "global.h"

Inverters::Inverters(State *parent) : QObject(parent), m_state(parent) {}

Inverters::~Inverters() { sDebug("inverters") << "cleanup"; }
