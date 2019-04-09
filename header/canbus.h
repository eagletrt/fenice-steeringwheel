#ifndef CANBUS_H
#define CANBUS_H

#include <QTimer>
#include <QByteArray>
#include <QHash>
#include "carstatus.h"

#include <QCanBus>

// CarStatus Constants
#define CAR_STATUS_IDLE    0
#define CAR_STATUS_SETUP   1
#define CAR_STATUS_RUN     2
#define CAR_STATUS_STOP    3

// ID in lettura
#define GET_CAN_STATUS          0xDA
#define GET_HV_STATE_ID         0xDB
#define GET_ERRORS_STATUS       0xDD
#define EXEC_MODE_ID            0xDF
#define GET_APPS_BSE_STATUS     0xDE
#define GET_STEER_STATUS        0xE1
#define BMS_STATUS_ID           0xEB
#define GET_ACTUATORS_RANGE_ACK 0xBC

// ID in Scrittura
// Ask again to check the CAN communication of peripherals
#define CHECK_CAN_COM           0xEA
#define ASK_HV_STATE_ID         0xEB
#define CHECK_SENSOR_ERROR_ID   0xEC
#define ASK_SENSORS_VALUE_ID    0xED
#define ASK_BATTERY_STATUS      0xEE
#define CHANGE_EXEC_MODE_ID     0xEF

//NEW DEFINE FOR VARANO 2018
#define STEERING_WHEEL_ID       0xA0
#define BMS_ID                  0xAA
#define LV_ID                   0xFF
#define ECU_MSG                 0x55
#define ECU_INV_LEFT            0x08
#define ECU_INV_RIGHT           0x09
#define ECU_ERRORS              0x01
#define STM_PEDALS              0xB0
#define GET_ACTUATORS_RANGE_ACK 0xBC
#define SET_ACTUATORS_RANGES    0xBB

// NEW 14/11

#define ENCODERS               0xD0

class Canbus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int actuatorRangePendingFlag READ actuatorRangePendingFlag NOTIFY actuatorRangePendingFlagCleared)

    public:
        Canbus(CarStatus* carStatus);
        ~Canbus();

        int invLeftState;
        int invRightState;
        int preChargeState;

        int warning;
        int error;        
        int ctrlIsEnabled;

        uint16_t m_speed;
        uint16_t m_invSxTemp;
        uint16_t m_invDxTemp;
        uint32_t m_hvTemp;
        uint32_t m_hvVolt;
        int m_lvVoltVal;
        int m_lvTemp;
        int m_lvVolt;

        int m_brakeVal;
        int m_throttleVal;
        int m_velocity;

        int velocity() const;
        int speed() const;
        int invSxTemp() const;
        int invDxTemp() const;
        int hvTemp() const;
        int lvTemp() const;
        int hvVolt() const;
        int lvVoltVal() const;
        int lvVolt() const;

        int brakeVal() const;
        int throttleVal() const;

        int ctrlIsOn;
        int goStatus;
        int map;
        int driveModeEnabled;

        int actuatorRangePendingFlag() const;

        int counterThrottle;
        int counterBrake;
        int counterSpeed;
        int pedalsPrescaler;
        int speedPrescaler;
        
        CarStatus* carStatus;

    private:
        QTimer *timerSteeringWheel;
        QTimer *timerStatus;
        QTimer *timerEnc;

        qint64 canID;
        QByteArray canMSG;
        QString canMessage;

        void parseCANMessage(int mid, QByteArray msg);
        void sendCanMessage(int, QByteArray);

        int idIsArrived;

        int m_actuatorRangePendingFlag;

    signals:
        void controlStateChanged(int ctrlState, int warn, int err);
        void presetChanged(int presetID);
        void pumpChanged(int pumpID);
        void actuatorRangePendingFlagCleared();

        //signal per qml hv e lv temp volt
        void speedChanged();
        void hvTempChanged();
        void lvTempChanged();
        void hvVoltChanged();
        void lvVoltChanged();
        void invSxTempChanged();
        void invDxTempChanged();

        void brakeValChanged();
        void throttleValChanged();

    public slots:
        void parseSerial();
        void toggleCar();
        void askHVUpdate(int);
        void setActuatorsRange(int, int);
        void checkCANCommunication(bool);
        void checkSensorsError();
        void steerConnected();
        void askStatus();
        void sendEncState();
        void askSetupOrIdle(int);
        void PWMCheck();
};

#endif // CANBUS_H
