#include "car/state.h"

#include <QDateTime>
#include <algorithm>
#include <cmath>

#include "global.h"

#define INVLIB_IMPLEMENTATION
#include "inverter.h"
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

  m_primary_messages_per_interface = {
      {m_telemetry, {primary_ID_TLM_STATUS}},
      {m_das, {primary_ID_CAR_STATUS}},
      {m_lv, {primary_ID_LV_CURRENT, primary_ID_LV_VOLTAGE, primary_ID_LV_TEMPERATURE, primary_ID_COOLING_STATUS}},
      {m_hv, {primary_ID_HV_CURRENT, primary_ID_HV_VOLTAGE, primary_ID_HV_TEMP, primary_ID_TS_STATUS}}};

  m_secondary_messages_per_interface = {{m_das, {secondary_ID_PEDALS_OUTPUT, secondary_ID_STEERING_ANGLE}},
                                        {m_telemetry, {secondary_ID_GPS_COORDS, secondary_ID_GPS_SPEED}}};

  QHashIterator<Interface *, QList<canlib_message_id>> primary_iterator(m_primary_messages_per_interface);
  while (primary_iterator.hasNext()) {
    primary_iterator.next();
    QList<canlib_message_id>::ConstIterator id;
    for (id = primary_iterator.value().begin(); id != primary_iterator.value().end(); ++id) {
      CANLIB_BITSET_ARRAY(m_primary_watchdog->activated, primary_watchdog_index_from_id(*id));
    }
  }

  QHashIterator<Interface *, QList<canlib_message_id>> secondary_iterator(m_secondary_messages_per_interface);
  while (secondary_iterator.hasNext()) {
    secondary_iterator.next();
    QList<canlib_message_id>::ConstIterator id;
    for (id = secondary_iterator.value().begin(); id != secondary_iterator.value().end(); ++id) {
      CANLIB_BITSET_ARRAY(m_secondary_watchdog->activated, secondary_watchdog_index_from_id(*id));
    }
  }

  m_watchdog_timer = new QTimer();
  m_watchdog_timer->setInterval(5000);
  connect(m_watchdog_timer, &QTimer::timeout, this, &State::timeout);
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

void State::timeout() {
  primary_watchdog_timeout(m_primary_watchdog, QDateTime::currentSecsSinceEpoch() * 1000);
  secondary_watchdog_timeout(m_secondary_watchdog, QDateTime::currentSecsSinceEpoch() * 1000);

  QHashIterator<Interface *, QList<canlib_message_id>> primary_iterator(m_primary_messages_per_interface);
  while (primary_iterator.hasNext()) {
    primary_iterator.next();
    QList<canlib_message_id>::ConstIterator id;
    bool invalid = true;
    for (id = primary_iterator.value().begin(); id != primary_iterator.value().end(); ++id) {
      bool timed_out = CANLIB_BITTEST_ARRAY(m_primary_watchdog->timeout, primary_watchdog_index_from_id(*id));
      if (timed_out) {
        char name[primary_MAX_MESSAGE_NAME_LENGTH];
        primary_message_name_from_id(*id, name);
      }
      invalid &= timed_out;
    }
    primary_iterator.key()->set_valid(!invalid);
  }

  QHashIterator<Interface *, QList<canlib_message_id>> secondary_iterator(m_secondary_messages_per_interface);
  while (secondary_iterator.hasNext()) {
    secondary_iterator.next();
    QList<canlib_message_id>::ConstIterator id;
    bool invalid = true;
    for (id = secondary_iterator.value().begin(); id != secondary_iterator.value().end(); ++id) {
      bool timed_out = CANLIB_BITTEST_ARRAY(m_secondary_watchdog->timeout, secondary_watchdog_index_from_id(*id));
      if (timed_out) {
        char name[secondary_MAX_MESSAGE_NAME_LENGTH];
        secondary_message_name_from_id(*id, name);
      }
      invalid &= timed_out;
    }
    secondary_iterator.key()->set_valid(!invalid);
  }
}

void State::handle_primary(quint32 id, uint8_t *raw) {
  primary_watchdog_reset(m_primary_watchdog, id, QDateTime::currentSecsSinceEpoch() * 1000);
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
    m_das->set_canlib_build_time(timestamp_conversion(data.canlib_build_time));
    break;
  }
  case primary_ID_HV_VERSION: {
    DESERIALIZE(primary, HV_VERSION);
    m_hv->set_version_component(data.component_version);
    m_hv->set_canlib_build_time(timestamp_conversion(data.canlib_build_time));
    break;
  }
  case primary_ID_LV_VERSION: {
    DESERIALIZE(primary, LV_VERSION);
    primary_deserialize_LV_VERSION(&data, raw);
    m_lv->set_version_component(data.component_version);
    m_hv->set_canlib_build_time(timestamp_conversion(data.canlib_build_time));
    break;
  }
  case primary_ID_TLM_VERSION: {
    DESERIALIZE(primary, TLM_VERSION);
    m_telemetry->set_version_component(data.component_version);
    m_telemetry->set_canlib_build_time(timestamp_conversion(data.canlib_build_time));
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
    // off-idle-on
    m_das->set_inverter_left(data.inverter_l);
    m_das->set_inverter_right(data.inverter_r);
    emit das_changed();
    break;
  }
  case primary_ID_INV_L_RESPONSE: {
    DESERIALIZE(primary, INV_L_RESPONSE);
    inverter_message_INV_RESPONSE *response_data = (inverter_message_INV_RESPONSE *)&data;

    m_inverters->set_left_errors(inverter_get_status(response_data));
    m_inverters->set_left_status(inverter_get_status(response_data));
    m_inverters->set_left_io_info(inverter_get_io_info(response_data));
    m_inverters->set_left_motor_temp(inverter_get_motor_temp(response_data));
    m_inverters->set_left_inverter_temp(inverter_get_inverter_temp(response_data));
    m_inverters->set_left_speed(inverter_get_speed(response_data));

    emit inverters_changed();
    break;
  }
  case primary_ID_INV_R_RESPONSE: {
    DESERIALIZE(primary, INV_R_RESPONSE);
    inverter_message_INV_RESPONSE *response_data = (inverter_message_INV_RESPONSE *)&data;

    m_inverters->set_right_errors(inverter_get_status(response_data));
    m_inverters->set_right_status(inverter_get_status(response_data));
    m_inverters->set_right_io_info(inverter_get_io_info(response_data));
    m_inverters->set_right_motor_temp(inverter_get_motor_temp(response_data));
    m_inverters->set_right_inverter_temp(inverter_get_inverter_temp(response_data));
    m_inverters->set_right_speed(inverter_get_speed(response_data));

    emit inverters_changed();
    break;
  }
  case primary_ID_LV_CURRENT: {
    DESERIALIZE_CONVERSION(primary, LV_CURRENT);
    m_lv->set_current(conversion.current);
    emit lv_changed();
    break;
  }
  case primary_ID_LV_VOLTAGE: {
    DESERIALIZE_CONVERSION(primary, LV_VOLTAGE);
    m_lv->set_voltage_1(conversion.voltage_1);
    m_lv->set_voltage_2(conversion.voltage_2);
    m_lv->set_voltage_3(conversion.voltage_3);
    m_lv->set_voltage_4(conversion.voltage_4);
    m_lv->set_voltage_min(qMin(conversion.voltage_2, qMin(conversion.voltage_3, conversion.voltage_4)));
    m_lv->set_voltage_max(qMax(conversion.voltage_2, qMax(conversion.voltage_3, conversion.voltage_4)));
    emit lv_changed();
    break;
  }
  case primary_ID_LV_TEMPERATURE: {
    DESERIALIZE_CONVERSION(primary, LV_TEMPERATURE);
    m_lv->set_dcdc_temperature(qMax(conversion.dcdc12_temperature, conversion.dcdc24_temperature));
    m_lv->set_battery_temperature(qMax(conversion.bp_temperature_1, conversion.bp_temperature_2));
    emit lv_changed();
    break;
  }
  case primary_ID_HV_CURRENT: {
    DESERIALIZE_CONVERSION(primary, HV_CURRENT);
    m_hv->set_current(conversion.current);
    m_hv->set_power(conversion.power);
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
  case primary_ID_HV_FEEDBACKS_STATUS: {
    DESERIALIZE(primary, HV_FEEDBACKS_STATUS);
    m_hv->set_feedbacks(data.feedbacks_status);
    emit hv_changed();
    break;
  }
  case primary_ID_DAS_ERRORS: {
    DESERIALIZE(primary, DAS_ERRORS);
    m_das->set_errors(data.das_error);
    emit das_changed();
    break;
  }
  case primary_ID_LV_ERRORS: {
    DESERIALIZE(primary, LV_ERRORS);
    m_lv->set_errors(data.errors);
    emit lv_changed();
    break;
  }
  }
}

void State::handle_secondary(quint32 id, uint8_t *raw) {
  secondary_watchdog_reset(m_secondary_watchdog, id, QDateTime::currentSecsSinceEpoch() * 1000);
  switch (id) {
  case secondary_ID_CONTROL_OUTPUT: {
    DESERIALIZE(secondary, CONTROL_OUTPUT);
    m_das->set_speed(data.estimated_velocity * 3.6);
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
