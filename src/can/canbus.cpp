#include "can/canbus.h"

#include <QPair>

#include "steering.h"

CanBus::CanBus(const CarStatus &status, QObject *parent) : QObject(parent), status(status) {}

CanBus::~CanBus() {
  sDebug("canbus") << "cleanup";

  QHash<CanDevice::Network, QPair<CanDevice *, QThread *>>::iterator iterator;
  for (iterator = devices.begin(); iterator != devices.end(); iterator++) {
    CanDevice *device = iterator->first;
    QThread *thread = iterator->second;

    thread->quit();
    if (!thread->wait(2000)) {
      thread->terminate();
      thread->wait();
    }

    delete device;
    delete thread;
  }
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
    sWarning("canbus") << errorString;
    sCritical("canbus") << "no can interfaces available!";
  }

  if (interfaces.length() == 0) {
    sCritical("canbus") << "no can interfaces available!";
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
          devices[network] = QPair<CanDevice *, QThread *>(device, thread);
        } else {
          sCritical("canbus") << errorString;
        }
      } else {
        sDebug("canbus") << "unrecognized interface:" << interfaceName;
      }
    }
  }
}

void CanBus::handleMessage(const CanDevice *device, int id, const QByteArray &message) {
  sDebug("canbus") << device->network << id << message;
}
