#include "car/lv.h"

#include "steering.h"

LV::LV(QObject* parent) : QObject(parent) {}

LV::~LV() {
  sDebug("lv") << "cleanup";
}
