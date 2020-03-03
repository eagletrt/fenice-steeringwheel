#include "../header/sensors.h"

Sensors::Sensors() {
    this->brakeVal = 100;
    this->throttleVal = 100;
    this->apps = 0;
    this->bse = 0;
    this->steer = 50;
}
void Sensors::setBrakeVal(int val) {
    brakeVal = val;
}
void Sensors::setThrottleVal(int val) {
    throttleVal = val;
}
void Sensors::setApps(int val) {
    apps = val;
}
void Sensors::setBse(int val) {
    bse = val;
}
void Sensors::setSteer(int val) {
    steer = val;
}
void Sensors::setNumErrApps(int val) {
    num_err_apps = val;
}
void Sensors::setNumErrBse(int val) {
    num_err_bse = val;
}
void Sensors::setNumErrSteer(int val) {
    num_err_steer = val;
}
int Sensors::getBrakeVal()const {
    return brakeVal;
}
int Sensors::getThrottleVal()const {
    return throttleVal;
}
int Sensors::getApps()const {
    return apps;
}
int Sensors::getBse()const {
    return bse;
}
int Sensors::getSteer()const {
    return steer;
}
int Sensors::getNumErrApps()const {
    return num_err_apps;
}
int Sensors::getNumErrBse()const {
    return num_err_bse;
}
int Sensors::getNumErrSteer()const {
    return num_err_steer;
}