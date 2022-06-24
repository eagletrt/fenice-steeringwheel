#include "car/lv.h"

#include "car/state.h"

LV::LV(State *parent) : Interface(parent), m_state(parent) {}

LV::~LV() { sDebug("lv") << "cleanup"; }
