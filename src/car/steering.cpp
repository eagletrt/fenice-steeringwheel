#include "car/steering.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

#include <QFile>

Steering::Steering(State *parent) : QObject(parent), m_state(parent) {
  m_poll_timer = new QTimer(this);
  connect(m_poll_timer, &QTimer::timeout, this, &Steering::poll);
  m_poll_timer->start(STEERING_POLL_TIMER);
}

Steering::~Steering() {
  sDebug("steering") << "cleanup";
  delete m_poll_timer;
}

#define STEERING_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
#define STEERING_TEMP_SCALE 1000.

void Steering::poll() {
#ifdef Q_OS_LINUX
  // Read temperature
  QFile file(STEERING_TEMP_FILE);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QByteArray line = file.readLine();
    setTemperature(line.toFloat() / STEERING_TEMP_SCALE);
    emit m_state->steeringChanged();
    file.close();
  } else {
    sWarning("steering") << "couldn't open" << STEERING_TEMP_FILE << "to read temperature";
  }
#endif
}

void Steering::onButtonPressed(int button) {
  if (button == Buttons::BUTTON_TOP_LEFT) {
    setPtt(true);
  }
}

void Steering::onButtonReleased(int button) {
  if (button == Buttons::BUTTON_TOP_LEFT) {
    setPtt(false);
  }
}

void Steering::onManettinoLeftChanged(int value) {
  if (value <= TC_STATUS_SLIP_AND_TORQUE)
    setTractionControl((TCStatus)value);
}

void Steering::onManettinoRightChanged(int value) {
  float map = value * 20;
  if (map <= 100) {
    setMap(map);
  }
}
