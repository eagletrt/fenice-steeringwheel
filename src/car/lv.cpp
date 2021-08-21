#include "car/lv.h"

#include "car/state.h"

LV::LV(State *parent) : QObject(parent), m_state(parent) {}

LV::~LV() { sDebug("lv") << "cleanup"; }
