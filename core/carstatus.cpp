#include "../header/carstatus.h"

CarStatus::CarStatus() {
    qDebug() << "Car Status Init";

    m_invRight = 2;
    m_invLeft = 2;
    m_preCharge = 2;

    m_ctrlIsEnabled = -1;

    m_ctrlIsOn = 0;

    m_car_status = CAR_STATUS_IDLE;

    m_stateofcharge = -1;
    m_temperature = -1;

    m_err_apps = 2;
    m_err_bse = 2;
    m_err_steer = 2;
    m_err_wheel_left = 2;
    m_err_wheel_right = 2;
    m_err_gps = 2;
    m_err_imu_front = 2;
    m_err_imu_central = 2;
    m_err_imu_rear = 2;

    m_invr = 2;
    m_invl = 2;
    m_front = 2;
    m_central = 2;
    m_pedals = 2;
    m_rear = 2;
    m_lv = 2;
    m_hv = 2;

    m_velocity = 0;
    m_preset = 1;
    m_pump = 6;

    m_apps = 0;
    m_bse = 0;
    m_steer = 50;

    m_invSxTemp = 0;
    m_invDxTemp = 0;

    m_hvTemp = 70;
    m_hvVolt = 440;
    m_lvVoltVal = 120;
    m_lvVolt = 120;
    m_lvTemp = 30;
    m_speed = 100;

    m_brakeVal = 100;
    m_throttleVal = 100;

    speedPrescaler = 8;
    pedalsPrescaler = 6;
    counterSpeed = 0;
    counterThrottle = 0;
    counterBrake = 0;
}

void CarStatus::setLeftInverterTemperature(uint8_t val1, uint8_t val2){
    m_invSxTemp = (((val1 + (val2 * 256.0f) ) - 15797.0f ) / 112.1182f) * 10.0f;
    emit invSxTempChanged();
}

void CarStatus::setRightInverterTemperature(uint8_t val1, uint8_t val2){
    m_invDxTemp = (((val1 + val2 * 256.0f ) - 15797.0f ) / 112.1182f) * 10.0f;
    emit invDxTempChanged();
}

void CarStatus::setSpeed(int id, int val1, int val2, int prescaler){
    counterSpeed++;
    speedPrescaler = prescaler;

    if(id == 0x06){

        if(counterSpeed >= pedalsPrescaler){
            counterSpeed = 0;

            m_speed = ((uint8_t)val1 * 256 + (uint8_t)val2) / 10;
            emit speedChanged();
        }
    }

}

void CarStatus::setPedalsPrescaler(int prescaler){
    pedalsPrescaler = prescaler;
}

void CarStatus::setBrake(int val){
    counterBrake++;

    if(counterBrake >= pedalsPrescaler){
        counterBrake = 0;
        m_brakeVal = ( (int) val );
        emit brakeValChanged();
    }
}

void CarStatus::setThrottle(int val){
    counterThrottle++;

    if(counterThrottle >= pedalsPrescaler){

        counterThrottle = 0;

        m_throttleVal = ( (int) val);

        int currPercMap = 0;

        switch(getMap() + 1){

            case 1: currPercMap = -20; break;
            case 2: currPercMap = 20; break;
            case 3: currPercMap = 40; break;
            case 4: currPercMap = 60; break;
            case 5: currPercMap = 80; break;
            case 6: currPercMap = 100; break;
            default: currPercMap = -100; break;
        }
        m_velocity = (80.0 * currPercMap * m_throttleVal) / 10000.0;

        emit velocityChanged();
        emit throttleValChanged();
    }
}

void CarStatus::setLVStatus(uint8_t val1, uint8_t val2, uint8_t val3){

    m_lvVolt = val1;
    m_lvVoltVal = val2;
    m_lvTemp = val3;

    emit lvTempChanged();
    emit lvVoltChanged();

}

void CarStatus::setHVStatus(uint8_t id, uint8_t valVolt1, uint8_t valVolt2, uint8_t valVolt3, uint8_t valTemp1, uint8_t valTemp2){
    if(id == 0x01){
        m_hvVolt = ((valVolt1 << 16) + (valVolt2 << 8) + valVolt3 ) / 1000;
        emit hvVoltChanged();
        m_hvTemp = ((valTemp1 << 8) + valTemp2 ) / 10;

        emit hvTempChanged();
    }
}



void CarStatus::changePump(int pumpID) {

    //qDebug() << "Pump to change: " << pumpID;

    if (pumpID != LOOP_THROUGH_PUMPS) {
        m_pump = pumpID;
    } else {
        // Loop through presents from 1 to 8 --> Case Single Button for Preset change
        m_pump += 1;
        //qDebug() << m_preset;
        m_pump = m_pump > PUMP_NUMBER ? m_pump % PUMP_NUMBER : m_pump;
        //qDebug() << m_pump;
    }

    //qDebug() << "New Pump: " << m_pump;

    //emit pumpChanged();
}

void CarStatus::changePreset(int presetID) {

    //qDebug() << "Preset to change: " << presetID;

    if (presetID != LOOP_THROUGH_PRESETS) {
        // Change preset to presetID --> Case Hardware Wiper
        m_preset = presetID;
    } else {
        // Loop through presents from 1 to 8 --> Case Single Button for Preset change
        m_preset += 1;
        //qDebug() << m_preset;
        m_preset = m_preset > PRESET_NUMBER ? m_preset % PRESET_NUMBER : m_preset;
        //qDebug() << m_preset;
    }

    //qDebug() << "New Preset: " << m_preset;

    emit presetChanged();
}

QString CarStatus::CANStatus() const {
    qDebug() << "Asked CanStatus";
    return QString("%1%2%3%4%5%6%7%8").arg(QString::number(m_invr),
                                       QString::number(m_invl),
                                       QString::number(m_front),
                                       QString::number(m_central),
                                       QString::number(m_pedals),
                                       QString::number(m_rear),
                                       QString::number(m_lv),
                                       QString::number(m_hv));
}

QString CarStatus::HVStatus() const {
    qDebug() << "Asked HVStatus";
    return QString("%1%2%3").arg(QString::number(m_preCharge),
                                 QString::number(m_invLeft),
                                 QString::number(m_invRight));
}

QString CarStatus::ERRStatus() const {
    qDebug() << "Asked ERRStatus";
    return QString("%1%2%3%4%5%6%7%8%9")
        .arg(QString::number(m_err_apps),
             QString::number(m_err_bse),
             QString::number(m_err_wheel_left),
             QString::number(m_err_wheel_right),
             QString::number(m_err_steer),
             QString::number(m_err_imu_front),
             QString::number(m_err_gps),
             QString::number(m_err_imu_central),
             QString::number(m_err_imu_rear));
}

QList<int> CarStatus::APPSStatus() const {
    QList<int> appsStatusArr;
    appsStatusArr.append((int) m_apps);
    for (int var = 0; var < 5; ++var) {
       appsStatusArr.append(CarStatus::getBit(m_num_err_apps,var));
    }
    return appsStatusArr;
}

int CarStatus::getBit(unsigned char seq, int index){
    return (int)(seq >> index) & 1U;
}

QList<int> CarStatus::BSEStatus() const {
    QList<int> bseStatusArr;
    bseStatusArr.append((int) m_bse);
    for (int var = 0; var < 4; ++var) {
       bseStatusArr.append(CarStatus::getBit(m_num_err_bse,var));
    }
    return bseStatusArr;
}

QList<int> CarStatus::STEERStatus() const {
    QList<int> steerStatusArr;
    steerStatusArr.append((int) m_steer);
    steerStatusArr.append(CarStatus::getBit(m_num_err_steer,0));
    return steerStatusArr;
}

QString CarStatus::CTRLEnabled() const {
    //qDebug() << "Asked CTRLEnabled";
    return QString::number(m_ctrlIsOn);
}

void CarStatus::setSTEERStatus(int steer){
    m_steer = steer;

    emit STEERStatusChanged();
}

void CarStatus::setAPPSBSEStatus(int apps,
                                 int bse){
    m_apps = apps;
    m_bse = bse;

    emit APPSStatusChanged();
    emit BSEStatusChanged();
}

void CarStatus::setERRStatus(int err_apps,
                             int err_bse,
                             int err_wheel_left,
                             int err_wheel_right,
                             int err_steer,
                             int err_imu_front,
                             int err_gps,
                             int err_imu_central,
                             int err_imu_rear) {

    m_err_apps = err_apps;
    m_err_bse = err_bse;
    m_err_steer = err_steer;
    m_err_gps = err_gps;
    m_err_wheel_right = err_wheel_left;
    m_err_wheel_left = err_wheel_right;
    m_err_imu_front = err_imu_front;
    m_err_imu_central = err_imu_central;
    m_err_imu_rear = err_imu_rear;

    emit ERRStatusChanged();
}

void CarStatus::setCANStatus(int invr,
                             int invl,
                             int front,
                             int central,
                             int pedals,
                             int rear,
                             int hv,
                             int lv) {
    m_invr = invr;
    m_invl = invl;
    m_front = front;
    m_rear = rear;
    m_lv = lv;
    m_hv = hv;
    m_central = central;
    m_pedals = pedals;

    emit CANStatusChanged();
}

void CarStatus::setHVStatus(int preCharge,
                            int invLeft,
                            int invRight) {
    m_invRight = invRight;
    m_invLeft = invLeft;
    m_preCharge = preCharge;

    emit HVStatusChanged();
}

int CarStatus::getCtrlIsEnabled() {
    return m_ctrlIsEnabled;
}



void CarStatus::setCarStatus(int ctrlIsEnabled,
                             int ctrlIsOn,
                             int driveModeEnabled,
                             int warning,
                             int error) {

    m_ctrlIsEnabled = ctrlIsEnabled;
    m_ctrlIsOn = ctrlIsOn;
    //m_warning = warning;
    //m_error = error;
    m_car_status = driveModeEnabled;

    emit execModeChanged(ctrlIsEnabled, ctrlIsOn, warning, error);
    emit carStatusChanged();
}

void CarStatus::setCarMode(int mode){
   m_car_status = mode;
   emit carStatusChanged();
}

void CarStatus::setWarning(int on) {
    m_warning = on;
    emit warningChanged();
    qDebug() << "Warning: " << m_warning << endl;
}

void CarStatus::setError(int on) {
    m_error = on;
    emit errorChanged();
}

int CarStatus::carStatus() {
    // qDebug() << "Asked carStatus";
    // qDebug() << m_car_status;
    return m_car_status;
}

int CarStatus::getCurrentStatus() {
    return m_car_status;
}

int CarStatus::getPump() {
    return m_pump - 1;
}

int CarStatus::getMap() {
    return m_preset - 1;
}

int CarStatus::stopCar() {
    qDebug() << "Yuuu! Stoppo la car!";
    m_car_status = CAR_STATUS_STOP;

    emit toggleCar();

    return m_car_status;
}

int CarStatus::toggleCarStatus() {
   switch(m_car_status){
      case CAR_STATUS_IDLE:
         qDebug() << "CAR_STATUS_IDLE -> CAR_STATUS_SETUP";
         // Change the status of the car
         m_car_status = CAR_STATUS_IDLE;
         // Send CAN request to the CTRL
         emit toggleCar();
         break;
      case CAR_STATUS_SETUP:
        qDebug() << "CAR_STATUS_SETUP -> CAR_STATUS_RUN";
        // Change the status of the car
        m_car_status = CAR_STATUS_SETUP;
        // Send CAN request to the CTRL
        emit toggleCar();
        break;
      case CAR_STATUS_RUN:
        qDebug() << "CAR_STATUS_RUN -> CAR_STATUS_SETUP";
        // Change the status of the car
        m_car_status = CAR_STATUS_RUN;
        // Send CAN request to the CTRL
        emit toggleCar();
        break;
    }

    return m_car_status;
}

void CarStatus::setStateOfCharge(int stateofcharge) {
    m_stateofcharge = stateofcharge;
    emit socChanged(stateofcharge);
}

void CarStatus::setTemperature(int temperature) {
    m_temperature = temperature;
    emit tempChanged(temperature);
}

int CarStatus::toggleCtrl() {
    if (m_car_status == CAR_STATUS_RUN) {
        m_ctrlIsOn = m_ctrlIsOn ? 0 : 1;
        emit CTRLEnabledChanged();
        return m_ctrlIsOn;
    }
    return -1;
}

int CarStatus::pump() const {
    return m_pump;
}
int CarStatus::preset() const {
    return m_preset;
}
int CarStatus::velocity() const {
    return m_velocity;
}
int CarStatus::brakeVal() const {
    return m_brakeVal;
}
int CarStatus::throttleVal() const {
    return m_throttleVal;
}
int CarStatus::speed() const {
    return m_speed;
}
int CarStatus::invSxTemp() const {
    return m_invSxTemp;
}
int CarStatus::invDxTemp() const {
    return m_invDxTemp;
}
uint8_t CarStatus::hvTemp() const {
    return m_hvTemp;
}
uint8_t CarStatus::lvTemp() const {
    return m_lvTemp;

}
uint8_t CarStatus::hvVolt() const {
    return m_hvVolt;
}
uint8_t CarStatus::lvVoltVal() const {
  //qDebug << m_lvVoltVal;
    return m_lvVoltVal;
}
uint8_t CarStatus::lvVolt() const {
    return m_lvVolt;
}
int CarStatus::getCtrlIsOn() {
    return m_ctrlIsOn;
}
int CarStatus::warning() const {
    return m_warning;
}
int CarStatus::error() const {
    return m_error;
}

CarStatus::~CarStatus() {
    qDebug() << "Closing CarStatus...";
}
