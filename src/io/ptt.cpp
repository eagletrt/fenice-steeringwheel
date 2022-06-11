#include "io/ptt.h"

#include <wiringPi.h>

#define PTT_PIN 26 // GPIO 12

Ptt::Ptt(QObject *parent) : QObject(parent) { pinMode(PTT_PIN, OUTPUT); }

void Ptt::start() { digitalWrite(PTT_PIN, HIGH); }

void Ptt::stop() { digitalWrite(PTT_PIN, LOW); }
