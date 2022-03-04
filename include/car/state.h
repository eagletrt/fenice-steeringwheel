#ifndef STATE_H
#define STATE_H

#include <QObject>

#include "can/device.h"

#include "das.h"
#include "hv.h"
#include "inverters.h"
#include "lv.h"
#include "steering.h"
#include "telemetry.h"

class State : public QObject {
  Q_OBJECT
  Q_PROPERTY(quint32 timestamp MEMBER m_timestamp NOTIFY timestampChanged)
  Q_PROPERTY(DAS *das MEMBER m_das NOTIFY dasChanged)
  Q_PROPERTY(HV *hv MEMBER m_hv NOTIFY hvChanged)
  Q_PROPERTY(LV *lv MEMBER m_lv NOTIFY lvChanged)
  Q_PROPERTY(Inverters *inverters MEMBER m_inverters NOTIFY invertersChanged)
  Q_PROPERTY(Steering *steering MEMBER m_steering NOTIFY steeringChanged)
  Q_PROPERTY(Telemetry *telemetry MEMBER m_telemetry NOTIFY hvChanged)
public:
  State(QObject *parent = nullptr);
  ~State();

public:
  quint32 timestamp() { return m_timestamp; }
  const DAS *das() { return m_das; }
  const HV *hv() { return m_hv; }
  const LV *lv() { return m_lv; }
  const Inverters *inverters() { return m_inverters; }
  const Steering *steering() { return m_steering; }
  const Telemetry *telemetry() { return m_telemetry; }

signals:
  void sendMessage(const CanDevice::Network network, quint32 id, const QByteArray &message);
  void showPopup(const QString &message);

public slots:
  void handleMessage(const CanDevice *device, quint32 id, const QByteArray &message);

private:
  void handleTopicBroadcast(quint32 id, uint8_t *raw);
  void handleTopicSteer(quint32 id, uint8_t *raw);
  void handleTopicEcuSteer(quint32 id, uint8_t *raw);
  void handleTopicEcuSteerCart(quint32 id, uint8_t *raw);

signals:
  void timestampChanged();
  void dasChanged();
  void hvChanged();
  void lvChanged();
  void invertersChanged();
  void steeringChanged();
  void telemetryChanged();

private:
  quint32 m_timestamp = 0;
  DAS *m_das;
  HV *m_hv;
  LV *m_lv;
  Inverters *m_inverters;
  Steering *m_steering;
  Telemetry *m_telemetry;
};

#endif // STATE_H
