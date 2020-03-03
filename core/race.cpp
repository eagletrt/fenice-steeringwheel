#include "../header/race.h"

Race::Race()
{
    this->speed = 100;
    this->velocity = 0;
    this->km = 999;
}

void Race::setSpeed(int val1, int val2){
    this->speed = (((uint8_t)val1 * 256 + (uint8_t)val2));
}

void Race::setVelocity(int val){
    this->velocity = val;
}

void Race::setKm(int meter1, int meter2){
    this->km = (((uint8_t)meter1 << 8 ) + (uint8_t)meter2);
}

int Race::getSpeed() const{
    return this->speed;
}

int Race::getVelocity() const{
    return this->velocity;
}

int Race::getKm() const{
    return this->km;
}