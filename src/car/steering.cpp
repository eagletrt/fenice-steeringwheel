#include "car/steering.h"

#include "car/state.h"
#include "global.h"
#include "io/buttons.h"

#include <QFile>

#include <QHostAddress>
#include <QNetworkInterface>

Steering::Steering(State *parent) : Interface(parent), m_state(parent) {
  set_pm_values(POWER_MAP_VALUES);
  set_sc_values(SLIP_CONTROL_VALUES);
  set_tv_values(TORQUE_VECTORING_VALUES);

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
  mLastPressTime = QDateTime::currentMSecsSinceEpoch();
}

void Steering::button_released(int button) {
  if (button == Buttons::BUTTON_TOP_LEFT) {
    set_ptt(false);
  }

  if (button == Buttons::BUTTON_BOTTOM_LEFT && !on_calibration_tab()) {
    quint64 pressTime = QDateTime::currentMSecsSinceEpoch() - mLastPressTime;
    if (pressTime > LONG_PRESS_THRESHOLD) {
      set_debug_mode(!m_debug_mode);
    }
  }
}

void Steering::send_steer_status() {
  quint8 *data = new quint8[primary_SIZE_STEER_STATUS];
  primary_serialize_STEER_STATUS(data, (qint8)m_pm_values[m_power_map_index], (qint8)m_sc_values[m_slip_control_index],
                                 (qint8)m_tv_values[m_torque_vectoring_index]);
  QByteArray message((const char *)data, primary_SIZE_STEER_STATUS);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_STEER_STATUS, message);
  delete[] data;
}

void Steering::send_set_torque_vectoring(int torque_i) {
  qDebug() << "sending torque";
  set_torque_vectoring_index(torque_i);
  send_steer_status();
}

void Steering::send_set_slip_control(int slip_i) {
  qDebug() << "sending slip";
  set_slip_control_index(slip_i);
  send_steer_status();
}

void Steering::send_set_power_map(int map_i) {
  qDebug() << "sending power map";
  set_power_map_index(map_i);
  send_steer_status();
}

void Steering::send_pump_speed(int ps) {

  float pumps;
  switch ((Steering::PumpSpeed)ps) {
  case Steering::PumpSpeed::PUMPS_AUTO:
    pumps = -1.0f;
    break;
  case Steering::PumpSpeed::PUMPS_OFF:
    pumps = 0.0f;
    break;
  case Steering::PumpSpeed::PUMPS_025:
    pumps = 0.25f;
    break;
  case Steering::PumpSpeed::PUMPS_050:
    pumps = 0.50f;
    break;
  case Steering::PumpSpeed::PUMPS_075:
    pumps = 0.75f;
    break;
  case Steering::PumpSpeed::PUMPS_100:
    pumps = 1.0f;
    break;
  default:
    return;
    break;
  }

  set_pumps_speed(ps);
  qDebug() << "sending pump speed";

  primary_message_SET_PUMPS_SPEED set_pumps_speed;
  primary_conversion_to_raw_SET_PUMPS_SPEED(&set_pumps_speed, qBound(-1.f, pumps, 1.f));

  quint8 *data = new quint8[primary_SIZE_SET_PUMPS_SPEED];
  primary_serialize_struct_SET_PUMPS_SPEED(data, &set_pumps_speed);
  QByteArray pumps_message((const char *)data, primary_SIZE_SET_PUMPS_SPEED);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_PUMPS_SPEED, pumps_message);
  delete[] data;
}

void Steering::send_radiators_speed(int rs) {

  float radiators;
  switch ((Steering::RadiatorSpeed)rs) {
  case Steering::RadiatorSpeed::RADIATORS_AUTO:
    radiators = -1.0f;
    break;
  case Steering::RadiatorSpeed::RADIATORS_OFF:
    radiators = 0.0f;
    break;
  case Steering::RadiatorSpeed::RADIATORS_025:
    radiators = 0.25f;
    break;
  case Steering::RadiatorSpeed::RADIATORS_050:
    radiators = 0.50f;
    break;
  case Steering::RadiatorSpeed::RADIATORS_075:
    radiators = 0.75f;
    break;
  case Steering::RadiatorSpeed::RADIATORS_100:
    radiators = 1.0f;
    break;
  default:
    return;
    break;
  }

  set_radiators_speed(rs);
  qDebug() << "sending radiator speed";

  primary_message_SET_RADIATOR_SPEED set_radiator_speed;
  primary_conversion_to_raw_SET_RADIATOR_SPEED(&set_radiator_speed, qBound(-1.f, radiators, 1.f));

  quint8 *data = new quint8[primary_SIZE_SET_RADIATOR_SPEED];
  primary_serialize_struct_SET_RADIATOR_SPEED(data, &set_radiator_speed);
  QByteArray radiators_message((const char *)data, primary_SIZE_SET_RADIATOR_SPEED);
  emit m_state->send_message(CanDevice::Network::PRIMARY, primary_ID_SET_RADIATOR_SPEED, radiators_message);
  delete[] data;
}

void Steering::manettino_left_changed(int val) {
  if (debug_mode())
    send_pump_speed(val);
  else
    send_set_slip_control(val);
}

void Steering::manettino_right_changed(int val) { send_set_power_map(val); }

void Steering::manettino_center_changed(int val) {
  if (debug_mode())
    send_radiators_speed(val);
  else
    send_set_torque_vectoring(val);
}
