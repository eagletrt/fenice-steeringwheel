#define primary_NETWORK_IMPLEMENTATION
#define primary_IDS_IMPLEMENTATION
#define primary_WATCHDOG_IMPLEMENTATION

#include "primary/c/ids.h"
#include "primary/c/network.h"
#include "primary/c/watchdog.h"

#define secondary_NETWORK_IMPLEMENTATION
#define secondary_IDS_IMPLEMENTATION
#define secondary_WATCHDOG_IMPLEMENTATION

#include "secondary/c/ids.h"
#include "secondary/c/network.h"
#include "secondary/c/watchdog.h"

#include "can/device.h"

#include "global.h"

CanDevice::CanDevice(const Network network, QCanBusDevice *can, QObject *parent)
    : QObject(parent), network(network), m_can(can) {}

CanDevice::~CanDevice() {
  sDebug("candevice") << "cleanup";
  delete m_can;
}

void CanDevice::start() { connect(m_can, &QCanBusDevice::framesReceived, this, &CanDevice::parse); }

void CanDevice::stop() { disconnect(m_can, &QCanBusDevice::framesReceived, this, &CanDevice::parse); }

bool CanDevice::send_message(quint32 id, const QByteArray &message) {
  return m_can->writeFrame(QCanBusFrame(id, message));
}

void CanDevice::parse() {
  while (m_can->framesAvailable()) {
    QCanBusFrame frame = m_can->readFrame();
    QByteArray message = frame.payload();
    quint32 id = frame.frameId();
    if (id != 0) {
      emit message_received(this, id, message);
    }
  }
}
