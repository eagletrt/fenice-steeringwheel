#include "car/state.h"

#include <algorithm>
#include <cmath>

#include "global.h"

#include "can/primary.h"
#include "can/secondary.h"

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

#define STATE_TOPIC_MASK 0b00000011111

void State::handle_message(const CanDevice *, quint32 id, const QByteArray &message) {
  int length = message.length();
  uint8_t *raw = new uint8_t[length];
  memcpy(raw, message.data(), length * sizeof(uint8_t));

  quint32 topic = id & STATE_TOPIC_MASK;
  switch (topic) {
  case TOPIC_BROADCAST_FILTER:
    handle_topic_broadcast(id, raw);
    break;
  case TOPIC_STEER_FILTER:
    handle_topic_steer(id, raw);
    break;
  case TOPIC_DASnSTEER_FILTER:
    handle_topic_ecu_steer(id, raw);
    break;
  case TOPIC_DASnSTEERnCART_FILTER:
    handle_topic_ecu_steer_cart(id, raw);
    break;
  }

  delete[] raw;
}

void State::handle_topic_broadcast(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_TIMESTAMP: {
    primary_TIMESTAMP data;
    deserialize_primary_TIMESTAMP(raw, &data);
    m_timestamp = data.timestamp;
    emit timestamp_changed();
    break;
  }
  case ID_DAS_VERSION: {
    primary_DAS_VERSION data;
    deserialize_primary_DAS_VERSION(raw, &data);
    m_das->set_version_component(data.component_version);
    m_das->set_version_cancicd(data.cancicd_version);
    break;
  }
  case ID_HV_VERSION: {
    primary_HV_VERSION data;
    deserialize_primary_HV_VERSION(raw, &data);
    m_hv->set_version_component(data.component_version);
    m_hv->set_version_cancicd(data.cancicd_version);
    break;
  }
  case ID_LV_VERSION: {
    primary_LV_VERSION data;
    deserialize_primary_LV_VERSION(raw, &data);
    m_lv->set_version_component(data.component_version);
    m_lv->set_version_cancicd(data.cancicd_version);
    break;
  }
  case ID_TLM_VERSION: {
    primary_TLM_VERSION data;
    deserialize_primary_TLM_VERSION(raw, &data);
    m_telemetry->set_version_component(data.component_version);
    m_telemetry->set_version_cancicd(data.cancicd_version);
    break;
  }
  }
}

void State::handle_topic_steer(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_TLM_STATUS: {
    primary_TLM_STATUS data;
    deserialize_primary_TLM_STATUS(raw, &data);
    m_telemetry->set_status((Telemetry::TlmStatus)data.tlm_status);
    m_telemetry->set_race((Telemetry::Race)data.race_type);
    m_telemetry->set_pilot(data.driver);
    m_telemetry->set_circuit(data.circuit);
    emit das_changed();
    break;
  }
  case ID_CAR_STATUS: {
    primary_CAR_STATUS data;
    deserialize_primary_CAR_STATUS(raw, &data);
    m_das->set_car_status((DAS::CarStatus)data.car_status);
    m_das->set_inverter_l((DAS::InverterStatus)data.inverter_l);
    m_das->set_inverter_r((DAS::InverterStatus)data.inverter_r);

    emit das_changed();
    break;
  }
  }
}

void State::handle_topic_ecu_steer(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_LV_CURRENT: {
    primary_LV_CURRENT data;
    deserialize_primary_LV_CURRENT(raw, &data);
    m_lv->set_current(data.current);
    emit lv_changed();
    break;
  }
  case ID_LV_VOLTAGE: {
    primary_LV_VOLTAGE data;
    deserialize_primary_LV_VOLTAGE(raw, &data);
    m_lv->set_voltage_1(data.voltage_1);
    m_lv->set_voltage_2(data.voltage_2);
    m_lv->set_voltage_3(data.voltage_3);
    m_lv->set_voltage_4(data.voltage_4);
    m_lv->set_total_voltage(data.total_voltage);
    emit lv_changed();
    break;
  }
  case ID_LV_TEMPERATURE: {
    primary_LV_TEMPERATURE data;
    deserialize_primary_LV_TEMPERATURE(raw, &data);
    m_lv->set_dcdc_temperature(data.dcdc_temperature);
    m_lv->set_battery_temperature(data.bp_temperature);
    emit lv_changed();
    break;
  }
  case ID_COOLING_STATUS: {
    primary_COOLING_STATUS data;
    deserialize_primary_COOLING_STATUS(raw, &data);
    m_lv->set_hv_fan_speed(data.hv_fan_speed);
    m_lv->set_lv_fan_speed(data.lv_fan_speed);
    m_lv->set_pump_speed(data.pump_speed);
    emit lv_changed();
    break;
  }
  }
}

void State::handle_topic_ecu_steer_cart(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_HV_CURRENT: {
    primary_HV_CURRENT data;
    deserialize_primary_HV_CURRENT(raw, &data);
    m_hv->set_current(data.current);
    m_hv->set_power(data.power);
    emit hv_changed();
    break;
  }
  case ID_HV_VOLTAGE: {
    primary_HV_VOLTAGE data;
    deserialize_primary_HV_VOLTAGE(raw, &data);
    m_hv->set_pack_voltage(data.pack_voltage);
    m_hv->set_bus_voltage(data.bus_voltage);
    m_hv->set_max_cell_voltage(data.max_cell_voltage);
    m_hv->set_min_cell_voltage(data.min_cell_voltage);
    emit hv_changed();
    break;
  }
  case ID_HV_TEMP: {
    primary_HV_TEMP data;
    deserialize_primary_HV_TEMP(raw, &data);
    m_hv->set_average_temperature(data.average_temp);
    m_hv->set_max_temperature(data.max_temp);
    m_hv->set_min_temperature(data.min_temp);
    emit hv_changed();
    break;
  }
  case ID_HV_ERRORS: {
    primary_HV_ERRORS data;
    deserialize_primary_HV_ERRORS(raw, &data);
    quint16 errors = ((quint16)data.errors[1] << 8) | data.errors[0];
    m_hv->set_errors(errors);
    quint16 warnings = ((quint16)data.warnings[1] << 8) | data.warnings[0];
    m_hv->set_warnings(warnings);
    emit hv_changed();
    break;
  }
  case ID_TS_STATUS: {
    primary_TS_STATUS data;
    deserialize_primary_TS_STATUS(raw, &data);
    m_hv->set_ts_status((HV::TsStatus)data.ts_status);
    emit hv_changed();
    break;
  }
  }
}
