#include "can/bus.h"

#include <QPair>

#include "global.h"

CanBus::CanBus(QObject *parent) : QObject(parent) {}

CanBus::~CanBus() {
  sDebug("canbus") << "cleanup";

  QHash<CanDevice::Network, QPair<CanDevice *, QThread *>>::iterator iterator;
  for (iterator = m_devices.begin(); iterator != m_devices.end(); iterator++) {
    CanDevice *device = iterator->first;
    QThread *thread = iterator->second;

    thread->quit();
    if (!thread->wait(2000)) {
      sDebug("canbus") << "thread timeout for network" << device->network;
      thread->terminate();
      thread->wait();
    }

    delete device;
    delete thread;
  }
}

void CanBus::handleMessage(const CanDevice *device, quint32 id, const QByteArray &message) {
  emit messageReceived(device, id, message);
}

bool CanBus::sendMessage(const CanDevice::Network network, quint32 id, const QByteArray &message) {
  if (m_devices.find(network) != m_devices.end()) {
    auto pair = m_devices[network];
    return pair.first->sendMessage(id, message);
  }
  sWarning("canbus") << "tried to send a message" << id << "on offline network" << network;
  return false;
}

void CanBus::start() {
  QString errorString;

#ifndef Q_OS_DARWIN
  const QList<QCanBusDeviceInfo> interfaces =
      QCanBus::instance()->availableDevices(QStringLiteral("socketcan"), &errorString);
#else
  const QList<QCanBusDeviceInfo> interfaces;
#endif

  if (!errorString.isEmpty()) {
    sCritical("canbus") << "error:" << errorString;
  }

  if (interfaces.isEmpty()) {
    sCritical("canbus") << "no can interfaces available";
  } else {
    sDebug("canbus") << "available can interfaces:" << interfaces.length();

    QList<QCanBusDeviceInfo>::const_iterator iterator;
    for (iterator = interfaces.begin(); iterator != interfaces.end(); iterator++) {
      QString interfaceName = iterator->name();
      if (networkMap.find(interfaceName) != networkMap.end()) {
        QString errorString;
        QCanBusDevice *can =
            QCanBus::instance()->createDevice(QStringLiteral("socketcan"), interfaceName, &errorString);
        if (can) {
          CanDevice::Network network = networkMap[interfaceName];
          sDebug("canbus") << interfaceName << "assigned to" << network;

          can->connectDevice();
          CanDevice *device = new CanDevice(network, can);
          QThread *thread = new QThread(this);

          connect(device, &CanDevice::messageReceived, this, &CanBus::handleMessage);
          connect(thread, &QThread::started, device, &CanDevice::start);

          device->moveToThread(thread);
          thread->start();
          m_devices[network] = QPair<CanDevice *, QThread *>(device, thread);
        } else {
          sCritical("canbus") << "error connecting to" << interfaceName << ":" << errorString;
        }
      } else {
        sDebug("canbus") << "unrecognized interface:" << interfaceName;
      }
    }
  }
}
