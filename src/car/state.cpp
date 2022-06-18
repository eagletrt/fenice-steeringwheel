#include "car/state.h"

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
}

State::~State() {
  sDebug("state") << "cleanup";
  delete m_das;
  delete m_hv;
  delete m_lv;
  delete m_steering;
  delete m_telemetry;
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

void State::handle_primary(quint32 id, uint8_t *raw) {
  switch (id) {
  case primary_id_TIMESTAMP: {
    primary_message_TIMESTAMP data;
    primary_deserialize_TIMESTAMP(&data, raw);
    m_timestamp = data.timestamp;
    emit timestamp_changed();
    break;
  }
  case primary_id_DAS_VERSION: {
    primary_message_DAS_VERSION data;
    primary_deserialize_DAS_VERSION(&data, raw);
    m_das->set_version_component(data.component_version);
    m_das->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_id_HV_VERSION: {
    primary_message_HV_VERSION data;
    primary_deserialize_HV_VERSION(&data, raw);
    m_hv->set_version_component(data.component_version);
    m_hv->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_id_LV_VERSION: {
    primary_message_LV_VERSION data;
    primary_deserialize_LV_VERSION(&data, raw);
    m_lv->set_version_component(data.component_version);
    m_lv->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_id_TLM_VERSION: {
    primary_message_TLM_VERSION data;
    primary_deserialize_TLM_VERSION(&data, raw);
    m_telemetry->set_version_component(data.component_version);
    m_telemetry->set_version_cancicd(data.cancicd_version);
    break;
  }
  case primary_id_TLM_STATUS: {
    primary_message_TLM_STATUS data;
    primary_deserialize_TLM_STATUS(&data, raw);
    m_telemetry->set_status(data.tlm_status);
    emit telemetry_changed();
    break;
  }
  case primary_id_CAR_STATUS: {
    primary_message_CAR_STATUS data;
    primary_deserialize_CAR_STATUS(&data, raw);
    m_das->set_car_status(data.car_status);
    m_das->set_inverter_left(data.inverter_l);
    m_das->set_inverter_right(data.inverter_r);
    emit das_changed();
    break;
  }
  case primary_id_LV_CURRENT: {
    primary_message_LV_CURRENT data;
    primary_deserialize_LV_CURRENT(&data, raw);
    m_lv->set_current(data.current);
    emit lv_changed();
    break;
  }
  case primary_id_LV_VOLTAGE: {
    primary_message_LV_VOLTAGE data;
    primary_deserialize_LV_VOLTAGE(&data, raw);
    primary_message_LV_VOLTAGE_conversion conversion;
    primary_raw_to_conversion_struct_LV_VOLTAGE(&conversion, &data);
    m_lv->set_voltage_1(conversion.voltage_1);
    m_lv->set_voltage_2(conversion.voltage_2);
    m_lv->set_voltage_3(conversion.voltage_3);
    m_lv->set_voltage_4(conversion.voltage_4);
    m_lv->set_voltage_min(
        qMin(conversion.voltage_1, qMin(conversion.voltage_2, qMin(conversion.voltage_3, conversion.voltage_4))));
    emit lv_changed();
    break;
  }
  case primary_id_LV_TEMPERATURE: {
    primary_message_LV_TEMPERATURE data;
    primary_deserialize_LV_TEMPERATURE(&data, raw);
    primary_message_LV_TEMPERATURE_conversion conversion;
    primary_raw_to_conversion_struct_LV_TEMPERATURE(&conversion, &data);
    m_lv->set_dcdc_temperature(conversion.dcdc12_temperature);
    m_lv->set_battery_temperature(conversion.bp_temperature_1);
    emit lv_changed();
    break;
  }
  case primary_id_COOLING_STATUS: {
    primary_message_COOLING_STATUS data;
    primary_deserialize_COOLING_STATUS(&data, raw);
    m_lv->set_radiators_speed(data.radiators_speed);
    m_lv->set_pumps_speed(data.pumps_speed);
    emit lv_changed();
    break;
  }
  case primary_id_HV_CURRENT: {
    primary_message_HV_CURRENT data;
    primary_deserialize_HV_CURRENT(&data, raw);
    m_hv->set_current(data.current);
    m_hv->set_power(data.power);
    emit hv_changed();
    break;
  }
  case primary_id_HV_VOLTAGE: {
    primary_message_HV_VOLTAGE data;
    primary_deserialize_HV_VOLTAGE(&data, raw);
    primary_message_HV_VOLTAGE_conversion conversion;
    primary_raw_to_conversion_struct_HV_VOLTAGE(&conversion, &data);
    m_hv->set_pack_voltage(conversion.pack_voltage);
    m_hv->set_bus_voltage(conversion.bus_voltage);
    m_hv->set_max_cell_voltage(conversion.max_cell_voltage);
    m_hv->set_min_cell_voltage(conversion.min_cell_voltage);
    emit hv_changed();
    break;
  }
  case primary_id_HV_TEMP: {
    primary_message_HV_TEMP data;
    primary_deserialize_HV_TEMP(&data, raw);
    primary_message_HV_TEMP_conversion conversion;
    primary_raw_to_conversion_struct_HV_TEMP(&conversion, &data);
    m_hv->set_average_temperature(conversion.average_temp);
    m_hv->set_max_temperature(conversion.max_temp);
    m_hv->set_min_temperature(conversion.min_temp);
    emit hv_changed();
    break;
  }
  case primary_id_HV_ERRORS: {
    primary_message_HV_ERRORS data;
    primary_deserialize_HV_ERRORS(&data, raw);
    m_hv->set_errors(data.errors);
    m_hv->set_warnings(data.warnings);
    emit hv_changed();
    break;
  }
  case primary_id_TS_STATUS: {
    primary_message_TS_STATUS data;
    primary_deserialize_TS_STATUS(&data, raw);
    m_hv->set_ts_status(data.ts_status);
    emit hv_changed();
    break;
  }
  }
}

void State::handle_secondary(quint32 id, uint8_t *raw) {
  switch (id) {
  case secondary_id_CONTROL_OUTPUT: {
    secondary_message_CONTROL_OUTPUT data;
    secondary_deserialize_CONTROL_OUTPUT(&data, raw);
    m_das->set_control_left(data.left);
    m_das->set_control_right(data.right);
    emit das_changed();
    break;
  }
  case secondary_id_PEDALS_OUTPUT: {
    secondary_message_PEDALS_OUTPUT data;
    secondary_deserialize_PEDALS_OUTPUT(&data, raw);
    secondary_message_PEDALS_OUTPUT_conversion conversion;
    secondary_raw_to_conversion_struct_PEDALS_OUTPUT(&conversion, &data);
    m_das->set_apps(conversion.apps);
    m_das->set_bse(conversion.bse_rear);
    emit das_changed();
    break;
  }
  case secondary_id_STEERING_ANGLE: {
    secondary_message_STEERING_ANGLE data;
    secondary_deserialize_STEERING_ANGLE(&data, raw);
    m_das->set_steering_angle(data.angle);
    emit das_changed();
    break;
  }
  case secondary_id_GPS_COORDS: {
    secondary_message_GPS_COORDS data;
    secondary_deserialize_GPS_COORDS(&data, raw);
    m_telemetry->set_latitude(data.latitude);
    m_telemetry->set_longitude(data.longitude);
    emit telemetry_changed();
    break;
  }
  case secondary_id_GPS_SPEED: {
    secondary_message_GPS_SPEED data;
    secondary_deserialize_GPS_SPEED(&data, raw);
    m_telemetry->set_gps_speed(data.speed);
    emit telemetry_changed();
    break;
  }
  }
}
