#include "car/steering.h"

#include "global.h"
#include "car/state.h"

#include <QFile>

Steering::Steering(State *parent) : QObject(parent), m_state(parent) {
  m_poll_timer = new QTimer(this);
  connect(m_poll_timer, &QTimer::timeout, this, &Steering::poll);
  m_poll_timer->start(STEERING_POLL_TIMER);
}

#define STEERING_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
#define STEERING_TEMP_SCALE 1000.

void Steering::poll() {
#ifdef Q_OS_LINUX
  // Read temperature
  QFile file(STEERING_TEMP_FILE);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QByteArray line = file.readLine();
    m_temperature = line.toFloat() / STEERING_TEMP_SCALE;
    emit temperatureChanged();
    emit m_state->steeringChanged();
    file.close();
  } else {
    sWarning("steering") << "couldn't open" << STEERING_TEMP_FILE << "to read temperature";
  }
#endif
}

Steering::~Steering() {
  sDebug("steering") << "cleanup";
  delete m_poll_timer;
}
