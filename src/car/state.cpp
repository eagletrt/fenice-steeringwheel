#include "car/state.h"

#include <QDateTime>
#include <algorithm>
#include <cmath>

#include "global.h"

#include "primary/c/ids.h"
#include "primary/c/network.h"
#include "secondary/c/ids.h"
#include "secondary/c/network.h"


State::State(QObject *parent) : QObject(parent) {
  m_das = new DAS(this);
  m_hv = new HV(this);
  m_lv = new LV(this);
  m_inverters = new Inverters(this);
  m_steering = new Steering(this);
  m_telemetry = new Telemetry(this);

  m_primary_watchdog = primary_watchdog_new();
  m_secondary_watchdog = secondary_watchdog_new();

  // activate all messages
  foreach (const quint32 key, m_primary_message_topic.keys()) {
    CANLIB_BITSET_ARRAY(m_primary_watchdog->activated, key);
  }
  foreach (const quint32 key, m_secondary_message_topic.keys()) {
    CANLIB_BITSET_ARRAY(m_secondary_watchdog->activated, key);
  }

  m_watchdog_timer = new QTimer();
  m_watchdog_timer->setInterval(5000);
  connect(m_watchdog_timer, &QTimer::timeout, this, [&]() -> void {
    primary_watchdog_timeout(m_primary_watchdog, QDateTime::currentMSecsSinceEpoch());
    secondary_watchdog_timeout(m_secondary_watchdog, QDateTime::currentMSecsSinceEpoch());
    foreach (const quint32 key, m_primary_message_topic.keys()) {
      bool timed_out = CANLIB_BITTEST_ARRAY(m_primary_watchdog->timeout, key);
      switch (m_primary_message_topic.value(key)) {
      case T_DAS: {
        if (m_das->valid() != timed_out) {
          m_das->set_valid(timed_out);
          emit m_das->valid_changed(timed_out);
        }
        break;
      }
      case T_HV: {
        if (m_hv->valid() != timed_out) {
          m_hv->set_valid(timed_out);
          emit m_hv->valid_changed(timed_out);
        }
        break;
      }
      case T_INVERTERS: {
        if (m_inverters->valid() != timed_out) {
          m_inverters->set_valid(timed_out);
          emit m_inverters->valid_changed(timed_out);
        }
        break;
      }
      case T_LV: {
        if (m_lv->valid() != timed_out) {
          m_lv->set_valid(timed_out);
          emit m_lv->valid_changed(timed_out);
        }
        break;
      }
      case T_TELEMETRY: {
        if (m_telemetry->valid() != timed_out) {
          m_telemetry->set_valid(timed_out);
          emit m_telemetry->valid_changed(timed_out);
        }
        break;
      }
      default:
          break;
      }
    }
    foreach (const quint32 key, m_secondary_message_topic.keys()) {
      bool timed_out = CANLIB_BITTEST_ARRAY(m_secondary_watchdog->timeout, key);
      switch (m_secondary_message_topic.value(key)) {
      case T_DAS: {
        if (m_das->valid() != timed_out) {
          m_das->set_valid(timed_out);
          emit m_das->valid_changed(timed_out);
        }
        break;
      }
      case T_HV: {
        if (m_hv->valid() != timed_out) {
          m_hv->set_valid(timed_out);
          emit m_hv->valid_changed(timed_out);
        }
        break;
      }
      case T_INVERTERS: {
        if (m_inverters->valid() != timed_out) {
          m_inverters->set_valid(timed_out);
          emit m_inverters->valid_changed(timed_out);
        }
        break;
      }
      case T_LV: {
        if (m_lv->valid() != timed_out) {
          m_lv->set_valid(timed_out);
          emit m_lv->valid_changed(timed_out);
        }
        break;
      }
      case T_TELEMETRY: {
        if (m_telemetry->valid() != timed_out) {
          m_telemetry->set_valid(timed_out);
          emit m_telemetry->valid_changed(timed_out);
        }
        break;
      }
      default:
          break;
      }
    }
  });
  m_watchdog_timer->start();
}

State::~State() {
  sDebug("state") << "cleanup";
  delete m_das;
  delete m_hv;
  delete m_lv;
  delete m_steering;
  delete m_telemetry;
  delete m_watchdog_timer;
  primary_watchdog_free(m_primary_watchdog);
  secondary_watchdog_free(m_secondary_watchdog);
}

void State::handle_message(const CanDevice *device, quint32 id, const QByteArray &message) {
  int length = message.length();
  uint8_t *raw = new uint8_t[length];
  memcpy(raw, message.data(), length * sizeof(uint8_t));

  // qDebug() << id << message;

  switch (device->network) {
  case CanDevice::Network::PRIMARY:
    handle_primary(id, raw);
    break;
  case CanDevice::Network::SECONDARY:
    handle_secondary(id, raw);
    break;
  }

  delete[] raw;
}

#define DESERIALIZE(network, message)                                                                                  \
  network##_message_##message data;                                                                                    \
  network##_deserialize_##message(&data, raw);

#define DESERIALIZE_CONVERSION(network, message)                                                                       \
  DESERIALIZE(network, message)                                                                                        \
  network##_message_##message##_conversion conversion;                                                                 \
  network##_raw_to_conversion_struct_##message(&conversion, &data);

void State::handle_primary(quint32 id, uint8_t *raw) {
  primary_watchdog_reset(m_primary_watchdog, id, QDateTime::currentMSecsSinceEpoch());
  switch (id) {
  case primary_ID_TIMESTAMP: {
    DESERIALIZE(primary, TIMESTAMP);
    m_timestamp = data.timestamp;
    emit timestamp_changed();
    break;
  }
  case primary_ID_DAS_VERSION: {
    DESERIALIZE(primary, DAS_VERSION);
    m_das->set_version_component(data.component_version);
    m_das->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_ID_HV_VERSION: {
    DESERIALIZE(primary, HV_VERSION);
    m_hv->set_version_component(data.component_version);
    m_hv->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_ID_LV_VERSION: {
    DESERIALIZE(primary, LV_VERSION);
    primary_deserialize_LV_VERSION(&data, raw);
    m_lv->set_version_component(data.component_version);
    m_lv->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_ID_TLM_VERSION: {
    DESERIALIZE(primary, TLM_VERSION);
    m_telemetry->set_version_component(data.component_version);
    m_telemetry->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_ID_TLM_STATUS: {
    DESERIALIZE(primary, TLM_STATUS);
    m_telemetry->set_status(data.tlm_status);
    emit telemetry_changed();
    break;
  }
  case primary_ID_CAR_STATUS: {
    DESERIALIZE(primary, CAR_STATUS);
    m_das->set_car_status(data.car_status);
    m_das->set_inverter_left(data.inverter_l);
    m_das->set_inverter_right(data.inverter_r);
    emit das_changed();
    break;
  }
  case primary_ID_LV_CURRENT: {
    DESERIALIZE(primary, LV_CURRENT);
    m_lv->set_current(data.current);
    emit lv_changed();
    break;
  }
  case primary_ID_LV_VOLTAGE: {
    DESERIALIZE_CONVERSION(primary, LV_VOLTAGE);
    m_lv->set_voltage_1(conversion.voltage_1);
    m_lv->set_voltage_2(conversion.voltage_2);
    m_lv->set_voltage_3(conversion.voltage_3);
    m_lv->set_voltage_4(conversion.voltage_4);
    m_lv->set_voltage_min(
        qMin(conversion.voltage_1, qMin(conversion.voltage_2, qMin(conversion.voltage_3, conversion.voltage_4))));
    emit lv_changed();
    break;
  }
  case primary_ID_LV_TEMPERATURE: {
    DESERIALIZE_CONVERSION(primary, LV_TEMPERATURE);
    m_lv->set_dcdc_temperature(conversion.dcdc12_temperature);
    m_lv->set_battery_temperature(conversion.bp_temperature_1);
    emit lv_changed();
    break;
  }
  case primary_ID_COOLING_STATUS: {
    DESERIALIZE_CONVERSION(primary, COOLING_STATUS);
    m_lv->set_radiators_speed(conversion.radiators_speed);
    m_lv->set_pumps_speed(conversion.pumps_speed);
    emit lv_changed();
    break;
  }
  case primary_ID_HV_CURRENT: {
    DESERIALIZE(primary, HV_CURRENT);
    m_hv->set_current(data.current);
    m_hv->set_power(data.power);
    emit hv_changed();
    break;
  }
  case primary_ID_HV_VOLTAGE: {
    DESERIALIZE_CONVERSION(primary, HV_VOLTAGE);
    m_hv->set_pack_voltage(conversion.pack_voltage);
    m_hv->set_bus_voltage(conversion.bus_voltage);
    m_hv->set_max_cell_voltage(conversion.max_cell_voltage);
    m_hv->set_min_cell_voltage(conversion.min_cell_voltage);
    emit hv_changed();
    break;
  }
  case primary_ID_HV_TEMP: {
    DESERIALIZE_CONVERSION(primary, HV_TEMP);
    m_hv->set_average_temperature(conversion.average_temp);
    m_hv->set_max_temperature(conversion.max_temp);
    m_hv->set_min_temperature(conversion.min_temp);
    emit hv_changed();
    break;
  }
  case primary_ID_HV_ERRORS: {
    DESERIALIZE(primary, HV_ERRORS);
    m_hv->set_errors(data.errors);
    m_hv->set_warnings(data.warnings);
    emit hv_changed();
    break;
  }
  case primary_ID_TS_STATUS: {
    DESERIALIZE(primary, TS_STATUS);
    m_hv->set_ts_status(data.ts_status);
    emit hv_changed();
    break;
  }
  }
}

void State::handle_secondary(quint32 id, uint8_t *raw) {
  secondary_watchdog_reset(m_secondary_watchdog, id, QDateTime::currentMSecsSinceEpoch());
  switch (id) {
  case secondary_ID_CONTROL_OUTPUT: {
    DESERIALIZE(secondary, CONTROL_OUTPUT);
    m_das->set_control_left(data.left);
    m_das->set_control_right(data.right);
    emit das_changed();
    break;
  }
  case secondary_ID_PEDALS_OUTPUT: {
    DESERIALIZE_CONVERSION(secondary, PEDALS_OUTPUT);
    m_das->set_apps(conversion.apps);
    m_das->set_bse(conversion.bse_rear);
    emit das_changed();
    break;
  }
  case secondary_ID_STEERING_ANGLE: {
    DESERIALIZE(secondary, STEERING_ANGLE);
    m_das->set_steering_angle(data.angle);
    emit das_changed();
    break;
  }
  case secondary_ID_GPS_COORDS: {
    DESERIALIZE(secondary, GPS_COORDS);
    m_telemetry->set_latitude(data.latitude);
    m_telemetry->set_longitude(data.longitude);
    emit telemetry_changed();
    break;
  }
  case secondary_ID_GPS_SPEED: {
    DESERIALIZE(secondary, GPS_SPEED);
    m_telemetry->set_gps_speed(data.speed);
    emit telemetry_changed();
    break;
  }
  }
}
