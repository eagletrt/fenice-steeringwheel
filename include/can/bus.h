#ifndef CANBUS_H
#define CANBUS_H

#include <QHash>
#include <QObject>
#include <QThread>

#include "can/device.h"

class CanBus : public QObject {
  Q_OBJECT

public:
  CanBus(QObject *parent = nullptr);
  ~CanBus();

  const QHash<QString, CanDevice::Network> networkMap =
      QHash<QString, CanDevice::Network>{{"vcan0", CanDevice::Network::PRIMARY},
                                         {"vcan1", CanDevice::Network::SECONDARY},
                                         {"can0", CanDevice::Network::PRIMARY},
                                         {"can1", CanDevice::Network::SECONDARY}};

public slots:
  void start();
  bool send_message(const CanDevice::Network network, quint32 id, const QByteArray &message);

protected slots:
  void handle_message(const CanDevice *device, quint32 id, const QByteArray &message);

signals:
  void message_received(const CanDevice *device, quint32 id, const QByteArray &message);

private:
  QHash<CanDevice::Network, QPair<CanDevice *, QThread *>> m_devices;
};

#endif // CANBUS_H
