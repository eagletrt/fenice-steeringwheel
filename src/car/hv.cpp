#include "car/hv.h"

#include "steering.h"

HV::HV(QObject* parent) : QObject(parent) {}

HV::~HV() {
  sDebug("hv") << "cleanup";
}