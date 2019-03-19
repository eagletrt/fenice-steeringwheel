#include "../header/canbus.h"
#include <QDebug>
#include <QFileInfo>

QCanBusDevice *device;

Canbus::Canbus(CarStatus* m_carStatus, const QString can_interface) {

   //Right Can for 5.10.1 RPI

   QString errorString;
   device = QCanBus::instance()->createDevice(
      QStringLiteral("socketcan"), QStringLiteral("vcan0"), &errorString);
      if (!device)
      qDebug() << "NO CAN!";
      else
      device->connectDevice();

      /*
      foreach (const QByteArray &backend, QCanBus::instance()->plugins()) {
      if (backend == can_interface) {
      qDebug() << "Socketcan Found";
      break;
   }
}

device = QCanBus::instance()->createDevice("socketcan", QStringLiteral("vcan0"));
device->connectDevice();
*/
carStatus = m_carStatus;

qDebug() << "CAN Interface Init";

timerSteeringWheel = new QTimer(this);
timerStatus = new QTimer(this);
timerEnc = new QTimer(this);

// Setup signal/slot mechanism
connect(timerSteeringWheel, SIGNAL(timeout()),
this, SLOT(steerConnected()));

connect(timerEnc, SIGNAL(timeout()),
this, SLOT(sendEncState()));

connect(timerStatus, SIGNAL(timeout()),
this, SLOT(askStatus()));

connect(device, SIGNAL(framesReceived()),
this, SLOT(parseSerial()));

connect(carStatus, SIGNAL(toggleCar()),
this, SLOT(toggleCar()));

connect(carStatus, SIGNAL(CTRLEnabledChanged()),
this, SLOT(toggleCar()));

timerEnc->start(500);
timerSteeringWheel->start(1000);
timerStatus->start(1000);

invLeftState = -1;
invRightState = -1;
preChargeState = -1;

error = -1;
warning = -1;


idIsArrived = 0;

m_actuatorRangePendingFlag = 0;

}

void Canbus::steerConnected() {
   QByteArray connected;
   connected.resize(8);
   connected[0] = 1;
   sendCanMessage(STEERING_WHEEL_ID,connected);
}

/*
Bisogna scegliere ID e come strutturare il Msg
cosi da avere l'ECU che cambia solo in RUN e SETUP
*/
void Canbus::sendEncState() {
   //only pump
   QByteArray state;
   state.resize(8);
   int pump = carStatus->getPump() + 1;

   switch(pump)
   {
      case 1:
      state[0] = 0x02;
      state[1] = 0x01;
      state[2] = 0x00;
      break;
      case 2:
      state[0] = 0x02;
      state[1] = 0x01;
      state[2] = 25;
      break;
      case 3:
      state[0] = 0x02;
      state[1] = 0x01;
      state[2] = 50;
      break;
      case 4:
      state[0] = 0x02;
      state[1] = 0x01;
      state[2] = 75;
      break;
      case 5:
      state[0] = 0x02;
      state[1] = 0x01;
      state[2] = 100;
      break;
      case 6:
      state[0] = 0x00;
      state[1] = 0x00;
      break;
   }
   //state[0] = 0x00;
   //state[1] = 0x00; //carStatus->getMap();
   //state[2] = carStatus->getPump();
   qDebug() << "updating pump with value " << carStatus->getPump();
   sendCanMessage(0xAF, state);
}

void Canbus::askStatus() {
   QByteArray askErrors;
   askErrors.resize(8);
   askErrors[0] = 0x02;
   sendCanMessage(STEERING_WHEEL_ID,askErrors);
}

void Canbus::PWMCheck() {
   QByteArray msg;
   msg.resize(8);
   msg[0] = 0x03;
   msg[1] = 0x01;

   goStatus = carStatus->getCurrentStatus();
   if(goStatus != CAR_STATUS_RUN)
   sendCanMessage(0xAF, msg);
}

int Canbus::actuatorRangePendingFlag() const {
   qDebug() << m_actuatorRangePendingFlag << "Asked m_actuatorRangePendingFlag";
   return m_actuatorRangePendingFlag;
}

void Canbus::checkSensorsError() {
   QByteArray vuoto;
   qDebug() << "CheckSensorsError";
   sendCanMessage(CHECK_SENSOR_ERROR_ID, vuoto);
}

void Canbus::checkCANCommunication(bool isOk = false) {
   QByteArray check;
   check.resize(8);
   if (isOk) {
      check[0] = 1;
      sendCanMessage(CHECK_CAN_COM, check);
   } else {
      check[0] = 0;
      sendCanMessage(CHECK_CAN_COM, check);
   }
}

void Canbus::parseCANMessage(int mid, QByteArray msg) {
   switch (mid) {
      case 0x181:
         if(msg.at(0) == 0x4a)
         {
            carStatus->setLeftInverterTemperature((uint8_t)msg.at(1),(uint8_t)msg.at(2));
         }
      break;

      case 0x182:
         if(msg.at(0) == 0x4a)
         {
            carStatus->setRightInverterTemperature((uint8_t)msg.at(1),(uint8_t)msg.at(2));
         }
      break;

      case STM_PEDALS:

         carStatus->setPedalsPrescaler(msg.at(4));

         if (msg.at(0) == 0x02){

            carStatus->setBrake(msg.at(1));

         }else{

            carStatus->setThrottle(msg.at(1));

         }

      break;

      case ENCODERS: // 0xD0

         carStatus->setSpeed(msg.at(0),msg.at(1),msg.at(2),msg.at(7));

      break;

      case GET_ACTUATORS_RANGE_ACK:
         switch (msg.at(0)) {
            case 0:
               if (msg.at(1) == 0){
                  //APPS min
                  qDebug() << "ACTUATORS_RANGE_ACK for APPS min";

                  m_actuatorRangePendingFlag = 3;
                  qDebug() << "DONE APPS MIN now press A for MAX";
                  emit actuatorRangePendingFlagCleared();
               }
               else if (msg.at(1) == 1){
                  //APPS max
                  qDebug() << "ACTUATORS_RANGE_ACK for APPS max";

                  m_actuatorRangePendingFlag = 0;
                  qDebug() << "DONE APPS MAX now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
            break;

            case 1:
               if (msg.at(1) == 0){
                  //BSE min
                  qDebug() << "ACTUATORS_RANGE_ACK for BSE min";

                  m_actuatorRangePendingFlag = 6;
                  qDebug() << "DONE BSE MIN now press A for MAX";
                  emit actuatorRangePendingFlagCleared();
               }
               else if (msg.at(1) == 1){
                  //BSE max
                  qDebug() << "ACTUATORS_RANGE_ACK for BSE max";
                  m_actuatorRangePendingFlag = 0;
                  qDebug() << "DONE BSE MAX now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
            break;

            case 2:
               if (msg.at(1) == 0){
                  //STEER min
                  qDebug() << "ACTUATORS_RANGE_ACK for STEER LEFT";
                  m_actuatorRangePendingFlag = 9;
                  qDebug() << "DONE STEER LEFT now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
               else if (msg.at(1) == 1){
                  //STEER max
                  qDebug() << "ACTUATORS_RANGE_ACK for STEER RIGHT";
                  m_actuatorRangePendingFlag = 0;
                  qDebug() << "DONE STEER RIGHT now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
            break;
      }
      break;

      case ECU_MSG:
      if(msg.at(0) == ECU_ERRORS){

         // -1 = 255 e -128 = 128, ovvero se tutti i bit sono a 1. Usate il qDebug sopra per scoprire il vostro valore magico
         //if((int)msg.at(1) == -1 && (int)msg.at(2) >= -128 && (int)msg.at(2) <= -1) // -1 = 255 e -128 = 128, ovvero se tutti i bit sono a 1. Usate il qDebug sopra per scoprire il vostro valore magico

         //VERSIONE PER ANTONIO DA SISTEMARE L'ORDINE E COSA MOSTRARE ERROR=5 WARNING=8

         // qDebug() << "Car CANBUS State: ";

         // qDebug() << "INV_LEFT: " << QString::number((msg.at(1) >> 0) & 1);
         // qDebug() << "INV_RIGHT: " << QString::number((msg.at(1) >> 1) & 1);
         // qDebug() << "PEDALS: " << QString::number((msg.at(1) >> 2) & 1);
         // qDebug() << "BMS_HV: " << QString::number((msg.at(1) >> 3) & 1);
         // qDebug() << "BMS_LV: " << QString::number((msg.at(1) >> 4) & 1);

         // qDebug() << "Errors State:";

         // qDebug() << "err_apps: " << QString::number((msg.at(2) >> 0) & 1);
         // qDebug() << "err_bse: " << QString::number((msg.at(2) >> 1) & 1);
         // qDebug() << "err_wheel_left: " << QString::number((msg.at(2) >> 2) & 1);
         // qDebug() << "err_wheel_right: " << QString::number((msg.at(2) >> 3) & 1);
         // qDebug() << "err_steer: " << QString::number((msg.at(2) >> 4) & 1);
         // qDebug() << "err_imu_front: " << QString::number((msg.at(2) >> 5) & 1);
         // qDebug() << "err_gps: " << QString::number((msg.at(2) >> 6) & 1);
         // qDebug() << "err_imu_central: " << QString::number((msg.at(2) >> 7) & 1);


         carStatus->setCANStatus((msg.at(1) >> 7) & 1,
                                 (msg.at(1) >> 6) & 1,
                                 (msg.at(1) >> 5) & 1,
                                 (msg.at(1) >> 4) & 1,
                                 (msg.at(1) >> 3) & 1,
                                 (msg.at(1) >> 2) & 1,
                                 (msg.at(1) >> 1) & 1,
                                 (msg.at(1) >> 0) & 1);

         carStatus->setERRStatus((msg.at(2) >> 7) & 1,
                                 (msg.at(2) >> 6) & 1,
                                 (msg.at(2) >> 5) & 1,
                                 (msg.at(2) >> 4) & 1,
                                 (msg.at(2) >> 3) & 1,
                                 (msg.at(2) >> 2) & 1,
                                 (msg.at(2) >> 1) & 1,
                                 (msg.at(2) >> 0) & 1,
                                 0);//vanno ancora sistemati qui si aspettava un altro valore

         if((int)msg.at(1) <= 0){
            qDebug() << "Error is 0" << (int)msg.at(1);
            carStatus->setError(0);
         }else{
            carStatus->setError(1);
            qDebug() << "Error is 1" << (int)msg.at(1);
         }

         if((int)msg.at(2) <= 0){
            qDebug() << "Warning is 0" << (int)msg.at(2);
            carStatus->setWarning(0);
         }else{
            carStatus->setWarning(1);
            qDebug() << "Warning is 1" << (int)msg.at(2);
         }

      } else if(msg.at(0) == ECU_INV_LEFT){
         QString oldStatus = carStatus->HVStatus();
         carStatus->setHVStatus(oldStatus.mid(0,1).toInt(), 1, oldStatus.mid(2,1).toInt());
         qDebug() << "Ricevuto Stato INV LEFT" << oldStatus.mid(0,1).toInt();
         qDebug() << oldStatus;
      } else if(msg.at(0) == ECU_INV_RIGHT){
         QString oldStatus = carStatus->HVStatus();
         carStatus->setHVStatus(oldStatus.mid(0,1).toInt(),oldStatus.mid(1,1).toInt(), 1);
         qDebug() << "Ricevuto Stato INV RIGHT" << oldStatus.mid(1,1).toInt();
         qDebug() << oldStatus;
      } else if(msg.at(0) == 0x03){

         //entro in start

         ctrlIsEnabled = carStatus->getCtrlIsEnabled();
         ctrlIsOn = carStatus->getCtrlIsOn();
         goStatus = carStatus->getCurrentStatus();
         // Get stop message
         // Get current map

         // NUOVA VERSIONE, DAL 20/02
         driveModeEnabled = 1; //dovrebbe voler dire msg.at(0)[0], aka il bit piu a dx
         //warning = msg.at(2);
         //error = msg.at(1);
         //velocity = ( (int) msg.at(1) ) / 2;


         if (!warning & !error & !ctrlIsEnabled) {
            ctrlIsEnabled = 1;
         }

         if (error) {
            // Stop the car
            ctrlIsEnabled = 0;
         }

         if (warning & !error) {
            ctrlIsEnabled = 0;
         }

         // Set the current Car Status
         carStatus->setCarStatus(ctrlIsEnabled,
            ctrlIsOn,
            driveModeEnabled,
            warning,
            error);

            QString oldStatus = carStatus->HVStatus();
            carStatus->setHVStatus(1, oldStatus.mid(1,1).toInt(), oldStatus.mid(2,1).toInt());

         }
         else if(msg.at(0) == 0x04) // idle
         {
            driveModeEnabled = 0;
            ctrlIsEnabled = carStatus->getCtrlIsEnabled();
            ctrlIsOn = carStatus->getCtrlIsOn();

            carStatus->setCarStatus(ctrlIsEnabled,
               ctrlIsOn,
               driveModeEnabled,
               0,
               0);

            }

            else if(msg.at(0) == 0x05) // go
            {
               driveModeEnabled = 2;
               ctrlIsEnabled = carStatus->getCtrlIsEnabled();
               ctrlIsOn = carStatus->getCtrlIsOn();

               carStatus->setCarStatus(ctrlIsEnabled,
                                       ctrlIsOn,
                                       driveModeEnabled,
                                       0,
                                       0);
               }
               else if(msg.at(0) == 0x06) // setup from run
               {
                  driveModeEnabled = 1;
                  ctrlIsEnabled = carStatus->getCtrlIsEnabled();
                  ctrlIsOn = carStatus->getCtrlIsOn();

                  carStatus->setCarStatus(ctrlIsEnabled,
                                          ctrlIsOn,
                                          driveModeEnabled,
                                          0,
                                          0);
         }
      break;

      case BMS_ID:

         carStatus->setHVStatus( (uint8_t)msg.at(0),
                                 (uint8_t)msg.at(1),
                                 (uint8_t)msg.at(2),
                                 (uint8_t)msg.at(3),
                                 (uint8_t)msg.at(4),
                                 (uint8_t)msg.at(5));

      break;

      case LV_ID:

         carStatus->setLVStatus( (uint8_t)msg.at(0),
                                 (uint8_t)msg.at(1),
                                 (uint8_t)msg.at(2));

      break;

      case BMS_STATUS_ID:

         if (msg.at(3) == 0x2A) {

            carStatus->setTemperature(msg.at(4));

         }

         if (msg.at(3) == 0xF) {

            carStatus->setStateOfCharge(msg.at(4));

         }
      break;

      // NON FUNZIONA BISOGNA FARLA NUOVA PRENDENDO DALLA STM FRONT
      case GET_STEER_STATUS:

         carStatus->setSTEERStatus(msg.at(0));

      break;

      // NON FUNZIONA BISOGNA FARLA NUOVA CON STM_PEDALS
      case GET_APPS_BSE_STATUS:

         carStatus->setAPPSBSEStatus(msg.at(0),msg.at(2));

      break;

   };
}

void Canbus::askSetupOrIdle(int whatState) {
   qDebug() << "pressed" << endl;
   if(whatState == 0) //GO TO IDLE
   {
      QByteArray msg;
      msg.resize(8);
      msg[0] = 0x04;
      sendCanMessage(0xA0, msg);
      //msg[0] = 0x00;
      //sendCanMessage(0x01, msg);
   }
   else if(whatState == 1) //GO TO SETUP
   {
      QByteArray msg;
      msg.resize(8);
      msg[0] = 0x03;
      sendCanMessage(0xA0, msg);
      //msg[0] = 0x01;
      //sendCanMessage(0x01, msg);
   }
}

void Canbus::toggleCar() {
   ctrlIsOn = carStatus->getCtrlIsOn();
   goStatus = carStatus->getCurrentStatus();
   map = carStatus->getMap();
   //int pump =  0;
   int pump = carStatus->getPump();

   QByteArray toggleCAN;
   toggleCAN.resize(8);
   qDebug() << "CtrlIsOn: " << ctrlIsOn;
   qDebug() << "GoIsOn: " << goStatus;
   qDebug() << "Map:" << map;
   qDebug() << "Pump:" << pump;

   if (goStatus == CAR_STATUS_STOP) {
      toggleCAN[0] = 0x07;
   } else {
      if(goStatus == CAR_STATUS_SETUP)
      toggleCAN[0] = 0x05;
      else if(goStatus == CAR_STATUS_RUN)
      toggleCAN[0] = 0x06;
      else if(goStatus == CAR_STATUS_IDLE)
      toggleCAN[0] = 0x16; // UBER TEMPORANEO

      switch (map) {
         case 0:
         toggleCAN[1] = -20;
         break;
         case 1:
         toggleCAN[1] = 20;
         break;
         case 2:
         toggleCAN[1] = 40;
         break;
         case 3:
         toggleCAN[1] = 60;
         break;
         case 4:
         toggleCAN[1] = 80;
         break;
         case 5:
         toggleCAN[1] = 100;
         break;
      }
      /*switch (pump) {
      case 0:
      toggleCAN[2] = -100;
      break;
      case 1:
      toggleCAN[2] = 1;
      break;
      case 2:
      toggleCAN[2] = 2;
      break;
      case 3:
      toggleCAN[2] = 3;
      break;
      case 4:
      toggleCAN[2] = 4;
      break;
      case 5:
      toggleCAN[2] = 5;
      break;
       }*/

   }

   qDebug() << canMessage;

   sendCanMessage(STEERING_WHEEL_ID, toggleCAN);
}

void Canbus::sendCanMessage(int id, QByteArray message) {
   QCanBusFrame frame;
   frame.setFrameId(id);
   frame.setPayload(message);
   device->writeFrame(frame);
}

void Canbus::askHVUpdate(int target) {
   QByteArray arrayTarget;
   arrayTarget.resize(8);
   if(target == 1)
      arrayTarget[0] = ECU_INV_LEFT;
      else if(target == 2)
         arrayTarget[0] = ECU_INV_RIGHT;

   if(target != 0)
   sendCanMessage(STEERING_WHEEL_ID, arrayTarget);
}

void Canbus::setActuatorsRange(int actuatorID, int rangeSide) {
   /*
   * Actuators ID:
   * 0: APPS
   * 1: BSE
   * 2: STEER
   *
   * Range Sides:
   * 0: MIN
   * 1: MAX
   */

   QByteArray actuator;
   actuator.resize(8);
   actuator[0] = actuatorID;
   actuator[1] = rangeSide;

   qDebug() << "setActuatorsRange for " << actuatorID << " for " << rangeSide;

   switch(actuatorID){
      case 0:

         if(rangeSide == 1){
            m_actuatorRangePendingFlag = 2;
         }else{
            m_actuatorRangePendingFlag = 1;
         }
         sendCanMessage(SET_ACTUATORS_RANGES, actuator);
      break;

      case 1:

         if(rangeSide == 1){
            m_actuatorRangePendingFlag = 5;
         }else{
            m_actuatorRangePendingFlag = 4;
         }
         sendCanMessage(SET_ACTUATORS_RANGES, actuator);

      break;

      case 2:

         if(rangeSide == 1){
            m_actuatorRangePendingFlag = 8;
         }else{
            m_actuatorRangePendingFlag = 7;
         }
         sendCanMessage(SET_ACTUATORS_RANGES, actuator);

      break;

      case 777:

         m_actuatorRangePendingFlag = 0;

      break;
   }

   emit actuatorRangePendingFlagCleared();
   /*
   QUESTO SERVE A MOSTRARE A UI CHE LA PROCEDURA È FINITA
   SETTO A 0 E FACCIO L'EMIT (NON VA INSERITO QUA MA IN FASE DI ACK)

   m_actuatorRangePendingFlag = 0;
   emit actuatorRangePendingFlagCleared();

   qDebug() << "actuatorRangePendingFlagCleared";
   */
}

void Canbus::parseSerial() {
   QByteArray canMsg;
   int canId;

   while(device->framesAvailable()){

      QCanBusFrame frame = device->readFrame();
      canMsg = frame.payload();
      canId = frame.frameId();

      if(canId != 0){
         parseCANMessage(canId,canMsg);
      }
   }
}

Canbus::~Canbus() {
   qDebug() << "Closing CAN...";
}
