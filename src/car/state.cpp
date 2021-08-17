#include "car/state.h"

#include "global.h"

#define __STDC_VERSION__ 201112

#include "Primary/c/Primary.h"
#include "Primary/can_config.h"
#include "Primary/ids.h"

#include "Secondary/c/Secondary.h"
#include "Secondary/can_config.h"
#include "Secondary/ids.h"

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
  case TOPIC_ACUnSTEER_FILTER:
    handleTopicAcuSteer(id, raw);
    break;
  case TOPIC_ACUnSTEERnCART_FILTER:
    handleTopicAcuSteerCart(id, raw);
    break;
  }

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
    emit ecuChanged();
    break;
  }
  case ID_CAR_STATUS: {
    Primary_CAR_STATUS data;
    deserialize_Primary_CAR_STATUS(raw, &data);
    emit ecuChanged();
    break;
  }
  }
}

void State::handleTopicAcuSteer(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_LV_CURRENT: {
    Primary_LV_CURRENT data;
    deserialize_Primary_LV_CURRENT(raw, &data);
    emit lvChanged();
    break;
  }
  case ID_LV_VOLTAGE: {
    Primary_LV_VOLTAGE data;
    deserialize_Primary_LV_VOLTAGE(raw, &data);
    emit lvChanged();
    break;
  }
  case ID_LV_TEMPERATURE: {
    Primary_LV_TEMPERATURE data;
    deserialize_Primary_LV_TEMPERATURE(raw, &data);
    emit lvChanged();
    break;
  }
  case ID_COOLING_STATUS: {
    Primary_COOLING_STATUS data;
    deserialize_Primary_COOLING_STATUS(raw, &data);
    emit lvChanged();
    break;
  }
  }
}

void State::handleTopicAcuSteerCart(quint32 id, uint8_t *raw) {
  switch (id) {
  case ID_HV_VOLTAGE: {
    Primary_HV_VOLTAGE data;
    deserialize_Primary_HV_VOLTAGE(raw, &data);
    emit hvChanged();
    break;
  }
  case ID_HV_CURRENT: {
    Primary_HV_CURRENT data;
    deserialize_Primary_HV_CURRENT(raw, &data);
    emit hvChanged();
    break;
  }
  case ID_HV_TEMP: {
    Primary_HV_TEMP data;
    deserialize_Primary_HV_TEMP(raw, &data);
    emit hvChanged();
    break;
  }
  case ID_HV_ERRORS: {
    Primary_HV_ERRORS data;
    deserialize_Primary_HV_ERRORS(raw, &data);
    emit hvChanged();
    break;
  }
  case ID_TS_STATUS: {
    Primary_TS_STATUS data;
    deserialize_Primary_TS_STATUS(raw, &data);
    emit hvChanged();
    break;
  }
  }
}
