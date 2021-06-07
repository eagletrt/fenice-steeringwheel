#include "can/device.h"

#include "steering.h"

CanDevice::CanDevice(const Network network, QCanBusDevice *can, QObject *parent)
    : QObject(parent), network(network), can(can) {}

CanDevice::~CanDevice() {
  sDebug("candevice") << "cleanup";
  delete can;
}

void CanDevice::start() { connect(can, &QCanBusDevice::framesReceived, this, &CanDevice::parse); }

void CanDevice::stop() { disconnect(can, &QCanBusDevice::framesReceived, this, &CanDevice::parse); }

void CanDevice::parse() {
  while (can->framesAvailable()) {
    QCanBusFrame frame = can->readFrame();
    QByteArray message = frame.payload();
    int id = frame.frameId();
    if (id != 0) {
      emit messageReceived(this, id, message);
    }
  }
}
