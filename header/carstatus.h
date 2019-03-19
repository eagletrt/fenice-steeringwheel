#ifndef CARSTATUS_H
#define CARSTATUS_H

#define CAR_STATUS_IDLE    0
#define CAR_STATUS_SETUP   1
#define CAR_STATUS_RUN     2
#define CAR_STATUS_STOP    3

#define PRESET_NUMBER      6
#define PUMP_NUMBER        6

#include <QDebug>

class CarStatus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString CANStatus READ CANStatus NOTIFY CANStatusChanged)
    Q_PROPERTY(QString HVStatus READ HVStatus NOTIFY HVStatusChanged)
    Q_PROPERTY(QString ERRStatus READ ERRStatus NOTIFY ERRStatusChanged)
    Q_PROPERTY(QString CTRLEnabled READ CTRLEnabled NOTIFY CTRLEnabledChanged)
    Q_PROPERTY(QList<int> APPSStatus READ APPSStatus NOTIFY APPSStatusChanged)
    Q_PROPERTY(QList<int> BSEStatus READ BSEStatus NOTIFY BSEStatusChanged)
    Q_PROPERTY(QList<int> STEERStatus READ STEERStatus NOTIFY STEERStatusChanged)
    Q_PROPERTY(int velocity READ velocity NOTIFY velocityChanged)
    Q_PROPERTY(int preset READ preset NOTIFY presetChanged)
    Q_PROPERTY(int pump READ pump NOTIFY pumpChanged)

    Q_PROPERTY(int warning READ warning NOTIFY warningChanged)
    Q_PROPERTY(int error READ error NOTIFY errorChanged)

    Q_PROPERTY(int carStatus READ carStatus NOTIFY carStatusChanged)

    Q_PROPERTY(int invSxTemp READ invSxTemp NOTIFY invSxTempChanged)
    Q_PROPERTY(int invDxTemp READ invDxTemp NOTIFY invDxTempChanged)

    Q_PROPERTY(int hvTemp READ hvTemp NOTIFY hvTempChanged)
    Q_PROPERTY(int lvTemp READ lvTemp NOTIFY lvTempChanged)
    Q_PROPERTY(int hvVolt READ hvVolt NOTIFY hvVoltChanged)
    Q_PROPERTY(int lvVolt READ lvVolt NOTIFY lvVoltChanged)
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int brakeVal READ brakeVal NOTIFY brakeValChanged)
    Q_PROPERTY(int throttleVal READ throttleVal NOTIFY throttleValChanged)


    public:
        CarStatus();
        ~CarStatus();

        const int LOOP_THROUGH_PRESETS = -1;
        const int LOOP_THROUGH_PUMPS = -1;

        QString CANStatus() const;
        QString HVStatus() const;
        QString ERRStatus() const;
        QList<int> APPSStatus() const;
        QList<int> BSEStatus() const;
        QList<int> STEERStatus() const;
        QString CTRLEnabled() const;

        int preset() const;
        int pump() const;
        int velocity() const;

        void setHVStatus(int invRight, int invLeft, int preCharge);
        void setCarStatus(int, int, int, int, int);
        void setCANStatus(int, int, int, int, int, int, int, int);
        void setERRStatus(int, int, int, int, int, int, int, int, int);
        void setAPPSBSEStatus(int, int);
        void setSTEERStatus(int);

        void setCarMode(int mode);

        int getCtrlIsEnabled();
        int getCtrlIsOn();
        int getCurrentStatus();
        int getMap();
        int getPump();

        int carStatus();
        void setWarning(int on);
        void setError(int on);

        int warning() const;
        int error() const;

        void setTemperature(int temperature);
        void setStateOfCharge(int stateofcharge);

        int speed() const;
        int invSxTemp() const;
        int invDxTemp() const;
        uint8_t hvTemp() const;
        uint8_t lvTemp() const;
        uint8_t hvVolt() const;
        uint8_t lvVoltVal() const;
        uint8_t lvVolt() const;

        int brakeVal() const;
        int throttleVal() const;

    public slots:
        int toggleCtrl();
        int toggleCarStatus();
        int stopCar();
        void changePreset(int presetID);
        void changePump(int pumpID);

        void setLeftInverterTemperature(uint8_t val1, uint8_t val2);
        void setRightInverterTemperature(uint8_t val1, uint8_t val2);
        void setSpeed(int id, int val1, int val2, int prescaler);
        void setPedalsPrescaler(int prescaler);
        void setThrottle(int val);
        void setBrake(int val);
        void setHVStatus(uint8_t id, uint8_t valVolt1, uint8_t valVolt2, uint8_t valVolt3, uint8_t valTemp1, uint8_t valTemp2);
        void setLVStatus(uint8_t val1, uint8_t val2, uint8_t val3);

    private:
        static int getBit(unsigned char seq, int index);
        int m_invRight;
        int m_invLeft;
        int m_preCharge;

        int m_ctrlIsEnabled;
        int m_ctrlIsOn;
        int m_car_status;

        int m_warning;
        int m_error;

        int m_stateofcharge;
        int m_temperature;
        int m_velocity;
        int m_preset;
        int m_pump;

        int m_invr;
        int m_invl;
        int m_front;
        int m_rear;
        int m_lv;
        int m_hv;
        int m_central;
        int m_pedals;

        int m_err_apps;
        int m_err_bse;
        int m_err_steer;
        int m_err_wheel_left;
        int m_err_wheel_right;
        int m_err_gps;
        int m_err_imu_front;
        int m_err_imu_central;
        int m_err_imu_rear;

        int m_apps;
        int m_num_err_apps;
        int m_bse;
        int m_num_err_bse;
        int m_steer;
        int m_num_err_steer;

        uint16_t m_invSxTemp;
        uint16_t m_invDxTemp;

        uint16_t m_speed;
        int m_hvTemp;
        int m_hvVolt;
        int m_lvVoltVal;
        int m_lvTemp;
        int m_lvVolt;
        int m_brakeVal;
        int m_throttleVal;

        int speedPrescaler;
        int pedalsPrescaler;
        int counterSpeed;
        int counterThrottle;
        int counterBrake ;

    signals:
        void tempChanged(int temperature);
        void socChanged(int soc);
        void execModeChanged(int ctrlIsEnabled, int ctrlIsOn, int warning, int error);
        void carStatusChanged();
        void warningChanged();
        void errorChanged();

        void toggleCar();

        void HVStatusChanged();
        void CANStatusChanged();
        void ERRStatusChanged();
        void APPSStatusChanged();
        void BSEStatusChanged();
        void STEERStatusChanged();
        void CTRLEnabledChanged();
        void velocityChanged();
        void presetChanged();
        void pumpChanged();


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

};

#endif // CARSTATUS_H
