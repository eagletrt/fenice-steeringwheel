#ifndef STATE_H
#define STATE_H

#include <QObject>

#include "can/device.h"

#include "ecu.h"
#include "hv.h"
#include "lv.h"
#include "pedals.h"
#include "telemetry.h"

class State : public QObject {
  Q_OBJECT
  Q_PROPERTY(ECU* ecu MEMBER m_ecu NOTIFY ecuChanged)
  Q_PROPERTY(HV* hv MEMBER m_hv NOTIFY hvChanged)
  Q_PROPERTY(LV* lv MEMBER m_lv NOTIFY lvChanged)
  Q_PROPERTY(Pedals* pedals MEMBER m_pedals NOTIFY pedalsChanged)
  Q_PROPERTY(Telemetry* telemetry MEMBER m_telemetry NOTIFY hvChanged)
public:
  State(QObject *parent = nullptr);
  ~State();

protected slots:
  void handleMessage(const CanDevice *device, int id, const QByteArray &message);

signals:
  void ecuChanged();
  void hvChanged();
  void lvChanged();
  void pedalsChanged();
  void telemetryChanged();

private:
  ECU *m_ecu;
  HV *m_hv;
  LV *m_lv;
  Pedals *m_pedals;
  Telemetry *m_telemetry;
};

#endif // STATE_H
