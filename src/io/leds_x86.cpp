#include "io/leds.h"

Leds::Leds(QObject *parent) : QObject(parent), m_left(nullptr), m_right(nullptr) {}

Leds::~Leds() {}

uint8_t Leds::set_left_brightness(const uint8_t, const uint8_t) { return false; }

uint8_t Leds::set_right_brightness(const uint8_t, const uint8_t) { return false; }
