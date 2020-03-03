#include "../header/inverters.h"

Inverters::Inverters()
{
    this->invLeft = 2;
    this->invRight = 2;
    this->preCharge = 2;
    this->invLeftTemp = 0;
    this->invRightTemp = 0;
}

void Inverters::setLeftInverter(int val) {
    this->invLeft = val;
}

void Inverters::setRightInverter(int val) {
    this->invRight = val;
}

void Inverters::setPreCharge(int val) {
    this->preCharge = val;
}

void Inverters::setLeftInverterTemperature(int val1, int val2) {
    this->invLeftTemp = (((val1 + (val2 * 256.0f) ) - 15797.0f ) / 112.1182f) * 10.0f;
}

void Inverters::setRightInverterTemperature(int val1, int val2) {
    this->invRightTemp = (((val1 + (val2 * 256.0f) ) - 15797.0f ) / 112.1182f) * 10.0f;
}

int Inverters::getLeftInverter() const{
    return this->invLeft;
}

int Inverters::getRightInverter() const{
    return this->invRight;
}

int Inverters::getPreCharge() const{
    return this->preCharge;
}

int Inverters::getLeftInverterTemperature() const{
    return this->invLeftTemp;
}

int Inverters::getRightInverterTemperature() const{
    return this->invRightTemp;
}