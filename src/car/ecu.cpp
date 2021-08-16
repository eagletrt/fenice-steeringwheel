#include "car/ecu.h"

#include "steering.h"

ECU::ECU(QObject* parent) : QObject(parent) {}

ECU::~ECU() {
  sDebug("ecu") << "cleanup";
}

