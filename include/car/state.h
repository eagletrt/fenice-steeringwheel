#ifndef STATE_H
#define STATE_H

#include <QColor>
#include <QHash>
#include <QObject>
#include <QTimer>

#include "can/device.h"
#include "primary/c/ids.h"
#include "primary/c/watchdog.h"
#include "secondary/c/ids.h"
#include "secondary/c/watchdog.h"

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
  void show_popup(const QString &message, QColor color = QColorConstants::White);

public slots:
  void handle_message(const CanDevice *device, quint32 id, const QByteArray &message);

private:
  enum message_topic { T_DAS, T_HV, T_INVERTERS, T_LV, T_STATE, T_STEERING, T_TELEMETRY };
  void handle_primary(quint32 id, uint8_t *raw);
  void handle_secondary(quint32 id, uint8_t *raw);
  void validate(message_topic central_unit);

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
  primary_watchdog *m_primary_watchdog;
  secondary_watchdog *m_secondary_watchdog;
  QTimer *m_watchdog_timer;

  const QHash<quint32, message_topic> m_primary_message_topic = {
      {primary_ID_DAS_VERSION, T_DAS},       {primary_ID_HV_VERSION, T_HV},        {primary_ID_LV_VERSION, T_LV},
      {primary_ID_TLM_VERSION, T_TELEMETRY}, {primary_ID_TLM_STATUS, T_TELEMETRY}, {primary_ID_CAR_STATUS, T_DAS},
      {primary_ID_LV_CURRENT, T_LV},         {primary_ID_LV_VOLTAGE, T_LV},        {primary_ID_LV_TEMPERATURE, T_LV},
      {primary_ID_COOLING_STATUS, T_LV},     {primary_ID_HV_CURRENT, T_HV},        {primary_ID_HV_TEMP, T_HV},
      {primary_ID_HV_ERRORS, T_HV},          {primary_ID_TS_STATUS, T_HV},
  };
  const QHash<quint32, message_topic> m_secondary_message_topic = {
      {secondary_ID_CONTROL_OUTPUT, T_DAS},      {secondary_ID_PEDALS_OUTPUT, T_DAS},
      {secondary_ID_STEERING_ANGLE, T_STEERING}, {secondary_ID_GPS_COORDS, T_TELEMETRY},
      {secondary_ID_GPS_SPEED, T_TELEMETRY},
  };
};

#endif // STATE_H
