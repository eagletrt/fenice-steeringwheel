#include "car/steering.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

#include <QFile>

#include <QHostAddress>
#include <QNetworkInterface>

Steering::Steering(State *parent) : Interface(parent), m_state(parent) {
  m_build_date_time =
      QStringLiteral(__DATE__) + QStringLiteral(" ") + QStringLiteral(__TIME__);

  m_canlib_build_hash = CANLIB_BUILD_HASH;
  m_canlib_build_time = timestamp_conversion(CANLIB_BUILD_TIME);
  
  m_poll_timer = new QTimer(this);
  connect(m_poll_timer, &QTimer::timeout, this, &Steering::poll);
  m_poll_timer->start(STEERING_POLL_TIMER);
  m_send_car_status_timer = new QTimer(this);
  connect(m_send_car_status_timer, &QTimer::timeout, this, &Steering::send_car_status);
  m_send_car_status_timer->start(primary_INTERVAL_STEER_STATUS);
}

Steering::~Steering() {
  sDebug("steering") << "cleanup";
  delete m_poll_timer;
  delete m_send_car_status_timer;
}

#define STEERING_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
#define STEERING_TEMP_SCALE 1000.

void Steering::poll() {
  // Update local ip address
  const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
  for (const QHostAddress &address : QNetworkInterface::allAddresses()) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost &&
        address.isInSubnet(QHostAddress::parseSubnet("192.168.0.0/12")))
      m_ip_addr = address.toString();
  }
#ifdef Q_OS_LINUX
  // Read temperature
  QFile file(STEERING_TEMP_FILE);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QByteArray line = file.readLine();
    set_temperature(line.toFloat() / STEERING_TEMP_SCALE);
    emit m_state->steering_changed();
    file.close();
  } else {
    sWarning("steering") << "couldn't open" << STEERING_TEMP_FILE << "to read temperature";
  }
#endif
}

void Steering::send_car_status() {
  quint8 *data = new quint8[primary_SIZE_STEER_STATUS];
  primary_serialize_STEER_STATUS(data, (primary_TractionControl)traction_control(), map());
  QByteArray steer_status((const char *)data, primary_SIZE_STEER_STATUS);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_STEER_STATUS, steer_status);
  delete[] data;
}

void Steering::button_pressed(int button) {
  if (button == Buttons::BUTTON_TOP_LEFT) {
    set_ptt(true);
  }
}

void Steering::button_released(int button) {
  if (button == Buttons::BUTTON_TOP_LEFT) {
    set_ptt(false);
  }
}

void Steering::manettino_left_changed(int value) {
  if (value <= primary_TractionControl_COMPLETE)
    set_traction_control((primary_TractionControl)value);
}

void Steering::manettino_right_changed(int value) {
  switch (value) {
  case 0:
    set_map(-20);
    break;
  case 1:
    set_map(20);
    break;
  case 2:
    set_map(40);
    break;
  case 3:
    set_map(60);
    break;
  case 4:
    set_map(80);
    break;
  case 5:
    set_map(100);
    break;
  default:
    return;
  }
}
