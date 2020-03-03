#include "../header/manettini.h"

Manettini::Manettini() {
    this->map = 1;
    this->pump = 6;
    this->tc = 1;
    this-> firstChange = true;
}
void Manettini::setMap(int val) {
    this->map = val;
}
void Manettini::setTc(int val) {
    this->tc = val;
}
void Manettini::setPump(int val) {
    this->pump = val;
}
void Manettini::setFirstChange() {
    firstChange = false;
}
int Manettini::getMap() const {
    return this->map;
}
int Manettini::getTc() const {
    return this->tc;
}
int Manettini::getPump() const {
    return this->pump;
}
bool Manettini::getFirstChange() const {
    return firstChange;
}
void Manettini::incMap(const int MAP_NUMBER) {
    map = (map + 1) % MAP_NUMBER;
}
void Manettini::incPump(const int PUMP_NUMBER) {
    pump = (pump + 1) % PUMP_NUMBER;
}
void Manettini::incTc(const int TC_NUMBER) {
    tc = (tc + 1) % TC_NUMBER;
}