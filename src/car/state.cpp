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

void State::handleMessage(const CanDevice *, quint32 id, const QByteArray &message) {
  int length = message.length();
  uint8_t *raw = new uint8_t[length];
  memcpy(raw, message.data(), length * sizeof(uint8_t));

  quint32 topic = id & STATE_TOPIC_MASK;
  switch (topic) {
  case TOPIC_BROADCAST_FILTER:
    handleTopicBroadcast(id, raw);
    break;
  case TOPIC_STEER_FILTER:
    handleTopicSteer(id, raw);
    break;
  case TOPIC_DASnSTEER_FILTER:
    handleTopicEcuSteer(id, raw);
    break;
  case TOPIC_DASnSTEERnCART_FILTER:
    handleTopicEcuSteerCart(id, raw);
    break;
  }

  delete[] raw;
}

void State::handleTopicBroadcast(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_TIMESTAMP: {
    primary_TIMESTAMP data;
    deserialize_primary_TIMESTAMP(raw, &data);
    m_timestamp = data.timestamp;
    emit timestampChanged();
    break;
  }
  case ID_DAS_VERSION: {
    primary_DAS_VERSION data;
    deserialize_primary_DAS_VERSION(raw, &data);
    m_das->setDasVersionCancicd(data.cancicd_version);
    m_das->setDasVersionComponent(data.component_version);
    break;
  }
  case ID_HV_VERSION: {
    primary_HV_VERSION data;
    deserialize_primary_HV_VERSION(raw, &data);
    m_das->setHvVersionCancicd(data.cancicd_version);
    m_das->setHvVersionComponent(data.component_version);
    break;
  }
  case ID_LV_VERSION: {
    primary_LV_VERSION data;
    deserialize_primary_LV_VERSION(raw, &data);
    m_das->setLvVersionCancicd(data.cancicd_version);
    m_das->setLvVersionComponent(data.component_version);
    break;
  }
  case ID_TLM_VERSION: {
    primary_TLM_VERSION data;
    deserialize_primary_TLM_VERSION(raw, &data);
    m_das->setTlmVersionCancicd(data.cancicd_version);
    m_das->setTlmVersionComponent(data.component_version);
    break;
  }
  }
}

void State::handleTopicSteer(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_TLM_STATUS: {
    primary_TLM_STATUS data;
    deserialize_primary_TLM_STATUS(raw, &data);
    m_telemetry->setStatus((Telemetry::TlmStatus)data.tlm_status);
    m_telemetry->setRace((Telemetry::Race)data.race_type);
    m_telemetry->setPilot(data.driver);
    m_telemetry->setCircuit(data.circuit);
    emit dasChanged();
    break;
  }
  case ID_CAR_STATUS: {
    primary_CAR_STATUS data;
    deserialize_primary_CAR_STATUS(raw, &data);
    m_das->setCarStatus((DAS::CarStatus)data.car_status);
    m_das->setInverterStatusLeft((DAS::InverterStatus)data.inverter_l);
    m_das->setInverterStatusRight((DAS::InverterStatus)data.inverter_r);
    
    emit dasChanged();
    break;
  }
  }
}

void State::handleTopicEcuSteer(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_LV_CURRENT: {
    primary_LV_CURRENT data;
    deserialize_primary_LV_CURRENT(raw, &data);
    m_lv->setCurrent(data.current);
    emit lvChanged();
    break;
  }
  case ID_LV_VOLTAGE: {
    primary_LV_VOLTAGE data;
    deserialize_primary_LV_VOLTAGE(raw, &data);
    m_lv->setVoltage1(data.voltage_1);
    m_lv->setVoltage2(data.voltage_2);
    m_lv->setVoltage3(data.voltage_3);
    m_lv->setVoltage4(data.voltage_4);
    m_lv->setTotalVoltage(data.total_voltage);
    emit lvChanged();
    break;
  }
  case ID_LV_TEMPERATURE: {
    primary_LV_TEMPERATURE data;
    deserialize_primary_LV_TEMPERATURE(raw, &data);
    m_lv->setDcdcTemperature(data.dcdc_temperature);
    m_lv->setBatteryTemperature(data.bp_temperature);
    emit lvChanged();
    break;
  }
  case ID_COOLING_STATUS: {
    primary_COOLING_STATUS data;
    deserialize_primary_COOLING_STATUS(raw, &data);
    m_lv->setHvFanSpeed(data.hv_fan_speed);
    m_lv->setLvFanSpeed(data.lv_fan_speed);
    m_lv->setPumpSpeed(data.pump_speed);
    emit lvChanged();
    break;
  }
  }
}

void State::handleTopicEcuSteerCart(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_HV_CURRENT: {
    primary_HV_CURRENT data;
    deserialize_primary_HV_CURRENT(raw, &data);
    m_hv->setCurrent(data.current);
    m_hv->setPower(data.power);
    emit hvChanged();
    break;
  }
  case ID_HV_VOLTAGE: {
    primary_HV_VOLTAGE data;
    deserialize_primary_HV_VOLTAGE(raw, &data);
    m_hv->setPackVoltage(data.pack_voltage);
    m_hv->setBusVoltage(data.bus_voltage);
    m_hv->setMaxCellVoltage(data.max_cell_voltage);
    m_hv->setMinCellVoltage(data.min_cell_voltage);
    emit hvChanged();
    break;
  }
  case ID_HV_TEMP: {
    primary_HV_TEMP data;
    deserialize_primary_HV_TEMP(raw, &data);
    m_hv->setAverageTemperature(data.average_temp);
    m_hv->setMaxTemperature(data.max_temp);
    m_hv->setMinTemperature(data.min_temp);
    emit hvChanged();
    break;
  }
  case ID_HV_ERRORS: {
    primary_HV_ERRORS data;
    deserialize_primary_HV_ERRORS(raw, &data);
    quint16 errors = ((quint16)data.errors[1] << 8) | data.errors[0];
    m_hv->setErrors(errors);
    quint16 warnings = ((quint16)data.warnings[1] << 8) | data.warnings[0];
    m_hv->setWarnings(warnings);
    emit hvChanged();
    break;
  }
  case ID_TS_STATUS: {
    primary_TS_STATUS data;
    deserialize_primary_TS_STATUS(raw, &data);
    m_hv->setTsStatus((HV::TsStatus)data.ts_status);
    emit hvChanged();
    break;
  }
  }
}
