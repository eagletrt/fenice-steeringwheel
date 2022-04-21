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
  Q_PROPERTY(quint32 timestamp MEMBER m_timestamp NOTIFY timestamp_changed)
  Q_PROPERTY(DAS *das MEMBER m_das NOTIFY das_changed)
  Q_PROPERTY(HV *hv MEMBER m_hv NOTIFY hv_changed)
  Q_PROPERTY(LV *lv MEMBER m_lv NOTIFY lv_changed)
  Q_PROPERTY(Inverters *inverters MEMBER m_inverters NOTIFY inverters_changed)
  Q_PROPERTY(Steering *steering MEMBER m_steering NOTIFY steering_changed)
  Q_PROPERTY(Telemetry *telemetry MEMBER m_telemetry NOTIFY hv_changed)
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
  void send_message(const CanDevice::Network network, quint32 id, const QByteArray &message);
  void show_popup(const QString &message);

public slots:
  void handle_message(const CanDevice *device, quint32 id, const QByteArray &message);

private:
  void handle_topic_broadcast(quint32 id, uint8_t *raw);
  void handle_topic_steer(quint32 id, uint8_t *raw);
  void handle_topic_ecu_steer(quint32 id, uint8_t *raw);
  void handle_topic_ecu_steer_cart(quint32 id, uint8_t *raw);

signals:
  void timestamp_changed();
  void das_changed();
  void hv_changed();
  void lv_changed();
  void inverters_changed();
  void steering_changed();
  void telemetry_changed();

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
