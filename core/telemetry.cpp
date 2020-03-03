#include "../header/telemetry.h"

Telemetry::Telemetry()
{
    for(int i = 0; i < NUM_TESTS; i++){
        test[i] = 0;
    }
    for(int i = 0; i < NUM_DRIVERS; i++) {
        driver[i] = 0;
    }
    test[0] = 1;
    driver[0] = 1;

    this->sender = false;
    this->telemetryEnStatus = 0; //0 off, 1 is setting up, 2 setted
    this->popup = "10steering \nwheel";
    this->ask = false;
}

//param val identify the id of the test to be enabled
void Telemetry::setTest(int val){
    bool found = false;
    int i = 0;
    while (!found && i < NUM_TESTS){
        if(test[i]) {
            test[i] = false;
            found = true;
        }
        i++;
    }
    
    test[val] = true;
}

//param val identify the id of the driver to be enabled
void Telemetry::setDriver(int val){
    bool found = false;
    int i = 0;
    while (!found && i < NUM_DRIVERS){
        if(driver[i]) {
            driver[i] = false;
            found = true;
        }
        i++;
    }
    
    driver[val] = true;
}

void Telemetry::setSender(){
    sender = !sender;
}

void Telemetry::setTelemetryStatus(int val){
    this->telemetryEnStatus = val;
}

void Telemetry::setPopupMessage(QChar priority, QChar color, QString msg){
    this->popup = "";
    popup.insert(0, priority);
    popup.insert(1, color);
    popup.append(msg);
}

void Telemetry::setAsk(bool ask) {
    this->ask = ask;
}

//void Telemetry::setTelemetryIndex(int index){
//    this->telemetry[index] = (telemetry[index] + 1) % 2;
//}

//return the id of the current test
int Telemetry::getTest() const{
    int pos = -1;
    int i = 0;
    bool found = false;

    while(!found && i < NUM_TESTS) {
        if(test[i]) {
            pos = i;
            found = true;
        }
        i++;
    }

    return pos;
}

int Telemetry::getDriver() const{
    int pos = -1;
    int i = 0;
    bool found = false;

    while(!found && i < NUM_DRIVERS) {
        if(driver[i]) {
            pos = i;
            found = true;
        }
        i++;
    }

    return pos;
}

bool Telemetry::getSender() const{
    return this->sender;
}

int Telemetry::getTelemetryStatus() const{
    return this->telemetryEnStatus;
}

QString Telemetry::getPopupMessage() const{
    return this->popup;
}

bool Telemetry::getAsk(){
    return !ask;
}

void Telemetry::getNUM(int* arr) {
    
    arr[0] = NUM_TESTS;
    arr[1] = NUM_DRIVERS;
    
}
