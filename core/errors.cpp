#include "../header/errors.h"

Errors::Errors() {
    this->err_apps = 2;
    this->err_bse = 2;
    this->err_steer = 2;
    this->err_wheel_left = 2;
    this->err_wheel_right = 2;
    this->err_gps = 2;
    this->err_imu_front = 2;
    this->err_imu_central = 2;
    this->err_imu_rear = 2;
    //Missing error's inizialization
}

void Errors::setErrApps(int val) {
    err_apps = val;
}
void Errors::setErrBse(int val) {
    err_bse = val;
}
void Errors::setErrSteer(int val) {
    err_steer = val;
}
void Errors::setErrLeftWheel(int val) {
    err_wheel_left = val;
}
void Errors::setErrRightWheel(int val) {
    err_wheel_right = val;
}
void Errors::setErrGps(int val) {
    err_gps = val;
}
void Errors::setErrFrontIMU(int val) {
    err_imu_front = val;
}
void Errors::setErrCentralIMU(int val) {
    err_imu_central = val;
}
void Errors::setErrRearIMU(int val) {
    err_imu_rear = val;
}
void Errors::setError(int val) {
    error = val;
}
void Errors::setAll(int err_apps,
                    int err_bse,
                    int err_steer,
                    int err_wheel_left,
                    int err_wheel_right,
                    int err_gps,
                    int err_imu_front,
                    int err_imu_central,
                    int err_imu_rear) {
    
    this->err_apps = err_apps;
    this->err_bse = err_bse;
    this->err_steer = err_steer;
    this->err_gps = err_gps;
    this->err_wheel_left = err_wheel_left;
    this->err_wheel_right = err_wheel_right;
    this->err_imu_front = err_imu_front;
    this->err_imu_central = err_imu_central;
    this->err_imu_rear = err_imu_rear;

}
int Errors::getErrApps() const{
    return err_apps;
}
int Errors::getErrBse() const{
    return err_bse;
}
int Errors::getErrSteer() const{
    return err_steer;
}
int Errors::getErrLeftWheel() const{
    return err_wheel_left;
}
int Errors::getErrRightWheel() const{
    return err_wheel_right;
}
int Errors::getErrGPS() const{
    return err_gps;
}
int Errors::getErrFrontIMU() const{
    return err_imu_front;
}
int Errors::getErrCentralIMU() const{
    return err_imu_central;
}
int Errors::getErrRearIMU() const{
    return err_imu_rear;
}
int Errors::getError() const{
    return error;
}