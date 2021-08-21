#ifndef STATE_H
#define STATE_H

#include <QObject>

#include "can/device.h"

#include "ecu.h"
#include "hv.h"
#include "lv.h"
#include "pedals.h"
#include "steering.h"
#include "telemetry.h"

class State : public QObject {
  Q_OBJECT
  Q_PROPERTY(quint32 timestamp MEMBER m_timestamp NOTIFY timestampChanged)
  Q_PROPERTY(ECU *ecu MEMBER m_ecu NOTIFY ecuChanged)
  Q_PROPERTY(HV *hv MEMBER m_hv NOTIFY hvChanged)
  Q_PROPERTY(LV *lv MEMBER m_lv NOTIFY lvChanged)
  Q_PROPERTY(Pedals *pedals MEMBER m_pedals NOTIFY pedalsChanged)
  Q_PROPERTY(Steering *steering MEMBER m_steering NOTIFY steeringChanged)
  Q_PROPERTY(Telemetry *telemetry MEMBER m_telemetry NOTIFY hvChanged)
public:
  State(QObject *parent = nullptr);
  ~State();

public slots:
  void handleMessage(const CanDevice *device, quint32 id, const QByteArray &message);

private:
  void handleTopicBroadcast(quint32 id, uint8_t *raw);
  void handleTopicSteer(quint32 id, uint8_t *raw);
  void handleTopicEcuSteer(quint32 id, uint8_t *raw);
  void handleTopicEcuSteerCart(quint32 id, uint8_t *raw);

signals:
  void timestampChanged();
  void ecuChanged();
  void hvChanged();
  void lvChanged();
  void pedalsChanged();
  void steeringChanged();
  void telemetryChanged();

private:
  quint32 m_timestamp = 0;
  ECU *m_ecu;
  HV *m_hv;
  LV *m_lv;
  Pedals *m_pedals;
  Steering *m_steering;
  Telemetry *m_telemetry;
};

#endif // STATE_H