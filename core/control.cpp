#include "../header/control.h"

Control::Control() {
    this->ctrlIsEnabled = -1; //-1 in order to avoid led enabling in RacingPage
    this->ctrlIsOn = 0;
    this->carStatus = 0;
}

void Control::setCtrlIsEnabled(bool val) {
    this->ctrlIsEnabled = val;
}

void Control::setCtrlIsOn(bool val) {
    this->ctrlIsOn = val;
}

bool Control::setCarStatus(int val) {
    if(this->carStatus = val)return true;
    return false;
}

bool Control::getCtrlIsEnabled() const {
    return this->ctrlIsEnabled;
}

bool Control::getCtrlIsOn() const{
    return this->ctrlIsOn;
}

int Control::getCarStatus() const {
    return this->carStatus;
}