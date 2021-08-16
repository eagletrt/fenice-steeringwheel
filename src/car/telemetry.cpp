#include "car/telemetry.h"

#include "steering.h"

Telemetry::Telemetry(QObject* parent) : QObject(parent) {}

Telemetry::~Telemetry() {
  sDebug("telemetry") << "cleanup";
}
