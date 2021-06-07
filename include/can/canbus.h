#ifndef CANBUS_H
#define CANBUS_H

#include <QObject>
#include <QThread>

#define __STDC_VERSION__ 201112
#include "Primary/c/Primary.h"
#include "Primary/can_config.h"
#include "Secondary/c/Secondary.h"
#include "Secondary/can_config.h"

#include "can/device.h"
#include "carstatus.h"

class CanBus : public QObject {
  Q_OBJECT

public:
  CanBus(const CarStatus &status, QObject *parent);
  ~CanBus();

  const QHash<QString, CanDevice::Network> networkMap =
      QHash<QString, CanDevice::Network>{{"vcan0", CanDevice::Network::PRIMARY},
                                         {"vcan1", CanDevice::Network::SECONDARY},
                                         {"can0", CanDevice::Network::PRIMARY},
                                         {"can1", CanDevice::Network::SECONDARY}};

  void start();

protected slots:
  void handleMessage(const CanDevice *device, int id, const QByteArray &message);

private:
  const CarStatus &status;
  QHash<CanDevice::Network, QPair<CanDevice *, QThread *>> devices;
};

#endif // CANBUS_H
