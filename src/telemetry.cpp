#include "telemetry.h"

Telemetry::Telemetry() {
  driver = 0;

  this->sender = false;
  this->telemetryEnStatus = 0; // 0 off, 1 is setting up, 2 setted
  this->popup =
      "10steering:wheel"; //'Priority' + 'Color' + 'Message' (: = \n) [Look in
                          // MainPage.qml for more informations]
  this->ask = false;
}

// param val identify the id of the test to be enabled
void Telemetry::setTest(int val) { test = val; }

// param val identify the id of the driver to be enabled
void Telemetry::setDriver(int val) { driver = val; }

void Telemetry::setRacetrack(int val) { racetrack = val; }

void Telemetry::setSender() { sender = !sender; }

void Telemetry::setTelemetryStatus(int val) { this->telemetryEnStatus = val; }

void Telemetry::setPopupMessage(QChar priority, QChar color, QString msg) {
  this->popup = "";
  popup.insert(0, priority);
  popup.insert(1, color);
  popup.append(msg);
}

void Telemetry::setAsk(bool ask) { this->ask = ask; }

// void Telemetry::setTelemetryIndex(int index){
//    this->telemetry[index] = (telemetry[index] + 1) % 2;
//}

// return the id of the current test
int Telemetry::getTest() const { return test; }

int Telemetry::getDriver() const { return driver; }

int Telemetry::getRacetrack() const { return racetrack; }

bool Telemetry::getSender() const { return this->sender; }

int Telemetry::getTelemetryStatus() const { return this->telemetryEnStatus; }

QString Telemetry::getPopupMessage() const { return this->popup; }

bool Telemetry::getAsk() { return !ask; }

void Telemetry::getNUM(int *arr) {
  arr[0] = NUM_TESTS;
  arr[1] = NUM_DRIVERS;
  arr[2] = NUM_RACETRACKS;
}
