#include "car/state.h"

#include "global.h"

#include "can/primary.h"
#include "can/secondary.h"

State::State(QObject *parent) : QObject(parent) {
  m_ecu = new ECU(this);
  m_hv = new HV(this);
  m_lv = new LV(this);
  m_pedals = new Pedals(this);
  m_steering = new Steering(this);
  m_telemetry = new Telemetry(this);
}

State::~State() {
  sDebug("state") << "cleanup";
  delete m_ecu;
  delete m_hv;
  delete m_lv;
  delete m_pedals;
  delete m_steering;
  delete m_telemetry;
}

#define STATE_TOPIC_MASK 0b00000011111

void State::handleMessage(const CanDevice *, quint32 id, const QByteArray &message) {
  int length = message.length();
  uint8_t *raw = new uint8_t[length];
  memcpy(raw, message.data(), (length - 1) * sizeof(uint8_t));

  quint32 topic = id & STATE_TOPIC_MASK;
  switch (topic) {
  case TOPIC_BROADCAST_FILTER:
    handleTopicBroadcast(id, raw);
    break;
  case TOPIC_STEER_FILTER:
    handleTopicSteer(id, raw);
    break;
  case TOPIC_ECUnSTEER_FILTER:
    handleTopicEcuSteer(id, raw);
    break;
  case TOPIC_ECUnSTEERnCART_FILTER:
    handleTopicEcuSteerCart(id, raw);
    break;
  }

  sDebug("state") << id << ":" << message;

  delete[] raw;
}

void State::handleTopicBroadcast(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_TIMESTAMP: {
    Primary_TIMESTAMP data;
    deserialize_Primary_TIMESTAMP(raw, &data);
    m_timestamp = data.timestamp;
    emit timestampChanged();
    break;
  }
  }
}

void State::handleTopicSteer(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_TLM_STATUS: {
    Primary_TLM_STATUS data;
    deserialize_Primary_TLM_STATUS(raw, &data);
    m_ecu->setTlmStatus((ECU::TlmStatus)data.tlm_status);
    m_ecu->setRaceType((ECU::RaceType)data.race_type);
    m_ecu->setDriver(data.driver);
    m_ecu->setCircuit(data.circuit);
    emit ecuChanged();
    break;
  }
  case ID_CAR_STATUS: {
    Primary_CAR_STATUS data;
    deserialize_Primary_CAR_STATUS(raw, &data);
    m_ecu->setCarStatus((ECU::CarStatus)data.car_status);
    m_ecu->setInverterStatusLeft((ECU::InverterStatus)data.inverter_l);
    m_ecu->setInverterStatusRight((ECU::InverterStatus)data.inverter_r);
    emit ecuChanged();
    break;
  }
  }
}

void State::handleTopicEcuSteer(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_LV_CURRENT: {
    Primary_LV_CURRENT data;
    deserialize_Primary_LV_CURRENT(raw, &data);
    m_lv->setCurrent(data.current);
    emit lvChanged();
    break;
  }
  case ID_LV_VOLTAGE: {
    Primary_LV_VOLTAGE data;
    deserialize_Primary_LV_VOLTAGE(raw, &data);
    m_lv->setVoltage1(data.voltage_1);
    m_lv->setVoltage2(data.voltage_2);
    m_lv->setVoltage3(data.voltage_3);
    m_lv->setVoltage4(data.voltage_4);
    m_lv->setTotalVoltage(data.total_voltage);
    emit lvChanged();
    break;
  }
  case ID_LV_TEMPERATURE: {
    Primary_LV_TEMPERATURE data;
    deserialize_Primary_LV_TEMPERATURE(raw, &data);
    m_lv->setDcdcTemperature(data.dcdc_temperature);
    m_lv->setBatteryTemperature(data.battery_temperature);
    emit lvChanged();
    break;
  }
  case ID_COOLING_STATUS: {
    Primary_COOLING_STATUS data;
    deserialize_Primary_COOLING_STATUS(raw, &data);
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
    Primary_HV_CURRENT data;
    deserialize_Primary_HV_CURRENT(raw, &data);
    m_hv->setCurrent(data.current);
    m_hv->setPower(data.power);
    emit hvChanged();
    break;
  }
  case ID_HV_VOLTAGE: {
    Primary_HV_VOLTAGE data;
    deserialize_Primary_HV_VOLTAGE(raw, &data);
    m_hv->setPackVoltage(data.pack_voltage);
    m_hv->setBusVoltage(data.bus_voltage);
    m_hv->setMaxCellVoltage(data.max_cell_voltage);
    m_hv->setMinCellVoltage(data.min_cell_voltage);
    emit hvChanged();
    break;
  }
  case ID_HV_TEMP: {
    Primary_HV_TEMP data;
    deserialize_Primary_HV_TEMP(raw, &data);
    m_hv->setAverageTemperature(data.average_temp);
    m_hv->setMaxTemperature(data.max_temp);
    m_hv->setMinTemperature(data.min_temp);
    emit hvChanged();
    break;
  }
  case ID_HV_ERRORS: {
    Primary_HV_ERRORS data;
    deserialize_Primary_HV_ERRORS(raw, &data);
    quint16 errors = ((quint16)data.errors[1] << 8) | data.errors[0];
    m_hv->setErrors(errors);
    quint16 warnings = ((quint16)data.warnings[1] << 8) | data.warnings[0];
    m_hv->setWarnings(warnings);
    emit hvChanged();
    break;
  }
  case ID_TS_STATUS: {
    Primary_TS_STATUS data;
    deserialize_Primary_TS_STATUS(raw, &data);
    m_hv->setTsStatus((HV::TsStatus)data.ts_status);
    emit hvChanged();
    break;
  }
  }
}
