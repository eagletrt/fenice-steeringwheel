#include "leds.h"

Leds::Leds(QObject *parent) : QObject(parent), left(nullptr), right(nullptr) {}

void Leds::pumpChanged(int) {}

void Leds::tractionControlChanged(int) {}

void Leds::animate() {}

Leds::~Leds() {}
