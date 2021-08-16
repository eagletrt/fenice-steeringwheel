#include "io/leds.h"

Leds::Leds(QObject *parent) : QObject(parent), left(nullptr), right(nullptr) {}

Leds::~Leds() {}
