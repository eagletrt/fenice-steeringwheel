#include "car/pedals.h"

#include "car/state.h"
#include "global.h"

Pedals::Pedals(State *parent) : QObject(parent), m_state(parent) {}

Pedals::~Pedals() { sDebug("pedals") << "cleanup"; }
