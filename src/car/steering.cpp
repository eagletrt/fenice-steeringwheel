#include "car/steering.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

#include <QFile>

#include <QHostAddress>
#include <QNetworkInterface>

Steering::Steering(State *parent) : Interface(parent), m_state(parent) {
  m_build_date_time = QStringLiteral(__DATE__) + QStringLiteral(" ") + QStringLiteral(__TIME__);

  m_canlib_build_hash = CANLIB_BUILD_HASH;
  m_canlib_build_time = timestamp_conversion(CANLIB_BUILD_TIME);

  m_poll_timer = new QTimer(this);
  connect(m_poll_timer, &QTimer::timeout, this, &Steering::poll);
  m_poll_timer->start(STEERING_POLL_TIMER);
  m_send_steer_status_timer = new QTimer(this);
  connect(m_send_steer_status_timer, &QTimer::timeout, this, &Steering::send_steer_status);
  m_send_steer_status_timer->start(primary_INTERVAL_STEER_STATUS);
}

Steering::~Steering() {
  sDebug("steering") << "cleanup";
  delete m_poll_timer;
  delete m_send_steer_status_timer;
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

void Steering::send_steer_status() {
  // qDebug() << "qua spedisco steer_status ma ora non c'e' :)";
  /*
  quint8* data = new quint8[primary_SIZE_STEER_STATUS];
  primary_serialize_STEER_STATUS(data, (qint8) m_power_map, (qint8) m_slip_control, (qint8) m_torque_vectoring);
  QByteArray message((const char *)data, primary_SIZE_STEER_STATUS);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_STEER_STATUS, message);
  delete[] data;
  */
}

void Steering::send_set_torque_vectoring(int torque_value) {
  qDebug() << "torque_value = " << torque_value;
  set_torque_vectoring((quint32)torque_value);
  send_steer_status();
}

void Steering::send_set_slip_control(int slip_value) {
  qDebug() << "torque_value = " << slip_value;
  set_slip_control((quint32)slip_value);
  send_steer_status();
}

void Steering::send_set_power_map(int map_value) {
  // TODO vedere sul volante quello che viene fuori
  qDebug() << "map value = " << map_value;
  switch (map_value) {
  case 0:
    set_power_map(-5);
    break;
  case 1:
    set_power_map(1);
    break;
  case 2:
    set_power_map(2);
    break;
  case 3:
    set_power_map(3);
    break;
  case 4:
    set_power_map(4);
    break;
  case 5:
    set_power_map(5);
    break;
  case 6:
    set_power_map(6);
    break;
  case 7:
    set_power_map(7);
    break;
  case 8:
    set_power_map(8);
    break;
  case 9:
    set_power_map(9);
    break;
  case 10:
    set_power_map(10);
    break;
  }
  send_steer_status();
}
