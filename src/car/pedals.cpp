#include "car/pedals.h"

#include "steering.h"

Pedals::Pedals(QObject* parent) : QObject(parent) {}

Pedals::~Pedals() {
  sDebug("pedals") << "cleanup";
}
