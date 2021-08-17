#include "can/device.h"

#include "global.h"

CanDevice::CanDevice(const Network network, QCanBusDevice *can, QObject *parent)
    : QObject(parent), network(network), can(can) {}

CanDevice::~CanDevice() {
  sDebug("candevice") << "cleanup";
  delete can;
}

void CanDevice::start() { connect(can, &QCanBusDevice::framesReceived, this, &CanDevice::parse); }

void CanDevice::stop() { disconnect(can, &QCanBusDevice::framesReceived, this, &CanDevice::parse); }

bool CanDevice::sendMessage(quint32 id, const QByteArray &message) { return can->writeFrame(QCanBusFrame(id, message)); }

void CanDevice::parse() {
  while (can->framesAvailable()) {
    QCanBusFrame frame = can->readFrame();
    QByteArray message = frame.payload();
    quint32 id = frame.frameId();
    if (id != 0) {
      emit messageReceived(this, id, message);
    }
  }
}
