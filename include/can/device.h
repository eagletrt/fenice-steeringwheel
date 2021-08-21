#ifndef DEVICE_H
#define DEVICE_H

#include <QCanBus>
#include <QObject>

class CanDevice : public QObject {
  Q_OBJECT

public:
  enum Network { PRIMARY, SECONDARY };
  Q_ENUM(Network)

public:
  CanDevice(const CanDevice::Network network, QCanBusDevice *can, QObject *parent = nullptr);
  ~CanDevice();

public slots:
  void start();
  void stop();
  bool sendMessage(quint32 id, const QByteArray &message);

protected slots:
  void parse();

signals:
  void messageReceived(const CanDevice *device, quint32 id, const QByteArray &message);

public:
  const Network network;

private:
  QCanBusDevice *m_can;
};

#endif // DEVICE_H
