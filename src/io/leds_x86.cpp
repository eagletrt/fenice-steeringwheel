#include "io/leds.h"

Leds::Leds(QObject *parent) : QObject(parent), m_left(nullptr), m_right(nullptr) {}

Leds::~Leds() {}
