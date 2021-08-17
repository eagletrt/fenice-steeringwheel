#include "car/pedals.h"

#include "global.h"
#include "car/state.h"

Pedals::Pedals(State* parent) : QObject(parent), m_state(parent) {}

Pedals::~Pedals() {
  sDebug("pedals") << "cleanup";
}
