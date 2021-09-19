#include "io/leds.h"

Leds::Leds(QObject *parent) : QObject(parent), m_left(nullptr), m_right(nullptr) {}

Leds::~Leds() {}

uint8_t Leds::setLeftBrightness(const uint8_t, const uint8_t) { return false; }

uint8_t Leds::setRightBrightness(const uint8_t, const uint8_t) { return false; }
