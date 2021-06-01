#include "detect.h"

#include "steering.h"

Detect::Detect(QCanBusDevice *device) { this->device = device; }

void Detect::startDevice() {
  connect(device, SIGNAL(framesReceived()), this, SLOT(getSerial()));
}

void Detect::getSerial() {
  QByteArray canMsg;
  int canId;

  while (device->framesAvailable()) {
    QCanBusFrame frame = device->readFrame();
    canMsg = frame.payload();
    canId = frame.frameId();
    if (canId != 0) {
      emit result(canId, canMsg);
    }
  }
}
