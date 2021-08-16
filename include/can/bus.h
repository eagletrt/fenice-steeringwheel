#ifndef CANBUS_H
#define CANBUS_H

#include <QObject>
#include <QThread>

#include "can/device.h"

class CanBus : public QObject {
  Q_OBJECT

public:
  CanBus(QObject *parent);
  ~CanBus();

  const QHash<QString, CanDevice::Network> networkMap =
      QHash<QString, CanDevice::Network>{{"vcan0", CanDevice::Network::PRIMARY},
                                         {"vcan1", CanDevice::Network::SECONDARY},
                                         {"can0", CanDevice::Network::PRIMARY},
                                         {"can1", CanDevice::Network::SECONDARY}};

public slots:
  void start();
  bool sendMessage(const CanDevice::Network network, int id, const QByteArray &message);

protected slots:
  void handleMessage(const CanDevice *device, int id, const QByteArray &message);

signals:
  void messageReceived(const CanDevice *device, int id, const QByteArray &message);

private:
  QHash<CanDevice::Network, QPair<CanDevice *, QThread *>> devices;
};

#endif // CANBUS_H
