#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>
#include <QVector>

#include "can/primary.h"
#include "global.h"

class State;

class Pilot {
  Q_GADGET
  Q_PROPERTY(quint8 id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)

public:
  quint8 id;
  QString name;
  Pilot() {}
  Pilot(quint8 id, const QString &name) : id(id), name(name) {}
  bool operator==(const Pilot &rhs) const { return id == rhs.id; };
  operator QString() const { return QString("Pilot(id: %1, name: %2)").arg(QString(id), name); }
};
Q_DECLARE_METATYPE(Pilot)

class Race {
  Q_GADGET
  Q_PROPERTY(quint8 id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)

public:
  quint8 id;
  QString name;
  Race() {}
  Race(quint8 id, const QString &name) : id(id), name(name) {}
  bool operator==(const Race &rhs) const { return id == rhs.id; };
  operator QString() const { return QString("Race(id: %1, name: %2)").arg(QString(id), name); }
};
Q_DECLARE_METATYPE(Race)

class Circuit {
  Q_GADGET
  Q_PROPERTY(quint8 id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(QString image MEMBER image)

public:
  quint8 id;
  QString name;
  QString image;
  Circuit() {}
  Circuit(quint8 id, const QString &name, const QString &image) : id(id), name(name), image(image) {}
  bool operator==(const Circuit &rhs) const { return id == rhs.id; }
  operator QString() const { return QString("Circuit(id: %1, name: %2)").arg(QString(id), name); }
};
Q_DECLARE_METATYPE(Circuit)

class Telemetry : public QObject {
  Q_OBJECT

public:
  enum TlmStatus { TLM_STATUS_ON = Primary_Tlm_Status_ON, TLM_STATUS_OFF = Primary_Tlm_Status_OFF };
  Q_ENUM(TlmStatus);

  S_PROPERTY(QVector<Pilot>, pilots, m_pilots, Pilots)
  S_PROPERTY(QVector<Race>, races, m_races, Races)
  S_PROPERTY(QVector<Circuit>, circuits, m_circuits, Tracks)
  S_PROPERTY(TlmStatus, status, m_status, Status)
  S_PROPERTY(quint8, pilot, m_pilot, Pilot, 0)
  S_PROPERTY(quint8, race, m_race, Race, 0)
  S_PROPERTY(quint8, circuit, m_circuit, Circuit, 0)
public:
  Telemetry(State *parent = nullptr);
  ~Telemetry();

protected slots:
  void sendStatus();

private:
  State *m_state;
};

#endif // TELEMETRY_H
