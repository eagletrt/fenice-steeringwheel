#include "io/leds.h"

#include <math.h>
#include <unistd.h>

#include <QDebug>

#include "wiringPiI2C.h"

TLC59108::TLC59108(const uint8_t address) : address(address) { fd = wiringPiI2CSetup(address); }

TLC59108::~TLC59108() { close(fd); }

uint8_t TLC59108::setRegister(const uint8_t reg, const uint8_t value) { return wiringPiI2CWriteReg8(fd, reg, value); }

uint8_t TLC59108::setRegisters(const uint8_t startReg, const uint8_t values[], const uint8_t numValues) {
  uint8_t buf[numValues + 1];
  buf[0] = startReg | AUTO_INCREMENT::IND;
  for (uint8_t i = 0; i < numValues; i++)
    buf[i + 1] = values[i];
  return write(fd, &buf, numValues + 1);
}

int TLC59108::readRegister(const uint8_t reg) const { return wiringPiI2CReadReg8(fd, reg); }

uint8_t TLC59108::readRegisters(uint8_t *dest, const uint8_t startReg, const uint8_t num) const {
  uint8_t qint8sRead = 0;
  while ((qint8sRead < num)) {
    (*dest) = (uint8_t)wiringPiI2CReadReg8(fd, startReg | AUTO_INCREMENT::ALL);
    dest++;
    qint8sRead++;
  }

  return qint8sRead;
}

bool TLC59108::getAllBrightness(uint8_t dutyCycles[]) const {
  return (readRegisters(dutyCycles, REGISTER::PWM0::ADDR, NUM_CHANNELS) == NUM_CHANNELS);
}

uint8_t TLC59108::init() { return setRegister(REGISTER::MODE1::ADDR, REGISTER::MODE1::ALLCALL); }

uint8_t TLC59108::setBrightness(const uint8_t pwmChannel, const uint8_t dutyCycle) {
  if (pwmChannel > 7)
    return ERROR::ERRINVAL;

  return setRegister(pwmChannel + 2, dutyCycle);
}

uint8_t TLC59108::setLedOutputMode(const uint8_t outputMode) {
  if (outputMode & 0xfc)
    return ERROR::ERRINVAL;

  uint8_t regValue = (outputMode << 6) | (outputMode << 4) | (outputMode << 2) | outputMode;

  uint8_t retVal = setRegister(REGISTER::LEDOUT0::ADDR, regValue);
  retVal &= setRegister(REGISTER::LEDOUT1::ADDR, regValue);
  return retVal;
}

uint8_t TLC59108::setAllBrightness(const uint8_t dutyCycle) {
  uint8_t buf[NUM_CHANNELS + 1];
  memset(&buf, dutyCycle, NUM_CHANNELS + 1);
  buf[0] = REGISTER::PWM0::ADDR | AUTO_INCREMENT::IND;
  return write(fd, &buf, NUM_CHANNELS + 1);
}

uint8_t TLC59108::setAllBrightnessDifferent(const uint8_t dutyCycles[]) {
  return setRegisters(REGISTER::PWM0::ADDR, dutyCycles, NUM_CHANNELS);
}

Leds::Leds(QObject *parent) : QObject(parent), left(new TLC59108(0x4a)), right(new TLC59108(0x45)) {
  left->init();
  right->init();
  left->setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
  right->setLedOutputMode(TLC59108::LED_MODE::PWM_IND);

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
  timer->start(30);
  //  left->setBrightness(6, 0x0);
  //  left->setBrightness(7, 0x0);
  //  right->setBrightness(7, 0xf);
}

void Leds::pumpChanged(int value) {
  left->setAllBrightness(0x0);
  left->setBrightness(value, 0xf);
}

void Leds::tractionControlChanged(int value) {
  right->setAllBrightness(0x0);
  right->setBrightness(value, 0xf);
}

void Leds::animate() {
  //  left->setAllBrightness(0x0);
  //  left->setAllBrightness(0x0);
  //  right->setAllBrightness(0xf - v);
  //  t += 0.1;
}

Leds::~Leds() {
  delete timer;
  left->setAllBrightness(0x0);
  right->setAllBrightness(0x0);
  delete left;
  delete right;
}
