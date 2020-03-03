#include "../header/canbus.h"
#include <QDebug>
#include <QFileInfo>

QCanBusDevice *device;

Canbus::Canbus(CarStatus* m_carStatus) {

   //Right Can for 5.10.1 RPI

   QString errorString;
   device = QCanBus::instance()->createDevice(
      QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
      if (!device)
         qDebug() << "NO CAN!";
      else
         device->connectDevice();

   carStatus = m_carStatus;

   timerSteeringWheel = new QTimer(this);
   timerStatus = new QTimer(this);
   timerEnc = new QTimer(this);
   timerTelemetry = new QTimer(this);

   connect(timerSteeringWheel, SIGNAL(timeout()),
   this, SLOT(steerConnected()));

   connect(timerEnc, SIGNAL(timeout()),
   this, SLOT(sendEncState()));

   connect(timerStatus, SIGNAL(timeout()),
   this, SLOT(askStatus()));

   connect(timerTelemetry, SIGNAL(timeout()),
   this, SLOT(sendTelemetry()));

   connect(device, SIGNAL(framesReceived()),
   this, SLOT(parseSerial()));

   connect(carStatus, SIGNAL(toggleCar()),
   this, SLOT(toggleCar()));

   connect(carStatus, SIGNAL(CTRLEnabledChanged()),
   this, SLOT(toggleCar()));

   timerEnc->start(500);
   timerSteeringWheel->start(1000);
   timerStatus->start(1000);
   timerTelemetry->start(33);

   invLeftState = -1;
   invRightState = -1;
   preChargeState = -1;

   error = -1;
   warning = -1;

   idIsArrived = 0;

   m_actuatorRangePendingFlag = 0;

}
// Send to ECU msg for presence in Can-Bus 
void Canbus::steerConnected() {
   QByteArray connected;
   connected.resize(8);
   connected[0] = 1;
   connected[1] = carStatus->getTc();
   connected[2] = carStatus->getPump();
   connected[3] = carStatus->getMap();
   sendCanMessage(STEERING_WHEEL_ID,connected);
}

void Canbus::sendMarker(){
   QByteArray marker;
   marker.resize(8);

   carStatus->setSteeringWheelPopup('0', '0', "MARKER");
   sendCanMessage(MARKER,marker);
}

// Send Status to Telemetry
void Canbus::sendTelemetry(){
   if(carStatus->getSender()) {
      //qDebug() << "-> sendTelemetry";
      QByteArray telemetry;
      telemetry.resize(8);
      telemetry = carStatus->getTelemetryStatus();
      //qDebug() << "---> sendingTelemetryStatus";
      //qDebug() << "telemetry[1] = " << telemetry[1] << "telemetry[2] = " << telemetry[2];
      sendCanMessage(TELEMETRY,telemetry);
   }
}

void Canbus::asktelemetry(){ 
   QByteArray telemetry;
   telemetry.resize(8);
   telemetry = carStatus->getTelemetryStatus();
   if(carStatus->TelemetryEnabledStatus() != 2) {
      carStatus->setTelemetryEnabledStatus(2);
   } else {
     telemetry = carStatus->abort();
   }
   sendCanMessage(STEERING_WHEEL_ID, telemetry);
}


//BROKEN DIOPORCO
// Send to ECU/Porchetto msg for pump state 
void Canbus::sendEncState() {
   QByteArray state;
   state.resize(8);
   int pump = carStatus->getPump() + 1;
   switch(pump){
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
      default:
         break;
   }
   
   sendCanMessage(0xAF, state);
}

// Send message to ECU to receive update for "stm" errors 
void Canbus::askStatus() {
   QByteArray askErrors;
   askErrors.resize(8);
   askErrors[0] = 0x02;

   map = carStatus->getMap();

   switch (map) {
      case 0:
         askErrors[1] = -20;
         break;
      case 1:
         askErrors[1] = 20;
         break;
      case 2:
         askErrors[1] = 40;
         break;
      case 3:
         askErrors[1] = 60;
         break;
      case 4:
         askErrors[1] = 80;
         break;
      case 5:
         askErrors[1] = 100;
         break;
   }

   sendCanMessage(STEERING_WHEEL_ID,askErrors);
}

// ???
void Canbus::PWMCheck() {
   QByteArray msg;
   msg.resize(8);
   msg[0] = 0x03;
   msg[1] = 0x01;

   goStatus = carStatus->carStatus();
   if(goStatus != CAR_STATUS_RUN)
   sendCanMessage(0xAF, msg);
}

// Get Actuator flag for pedals and steering calibration  
int Canbus::actuatorRangePendingFlag() const {
   return m_actuatorRangePendingFlag;
}

// Send Message to Sensors to receive sensors errors
void Canbus::checkSensorsError() {
   QByteArray vuoto;
   sendCanMessage(CHECK_SENSOR_ERROR_ID, vuoto);
}

// **TO_REMOVE** From TabSensors ask if Can Comunication is OK
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

// Ask if we can move to Set-Up/Idle state from Tab Status
void Canbus::askSetupOrIdle(int whatState) {
   
   QByteArray msg;
   msg.resize(8); 
   
   switch (whatState) {
      case 0:
         //GO TO IDLE
         msg[0] = 0x04;
         sendCanMessage(0xA0, msg);
         break;
      case 1:
         //GO TO SETUP
         msg[0] = 0x03;
         sendCanMessage(0xA0, msg);
         break;
      default:
         break;
   } 
}

// Idle -> Setup     0x03   
// Setup -> Idle     0x04
// Setup -> Run      0x05
// Run -> Setup      0x06


void Canbus::toggleCar() {
   QString popupMessage;
   ctrlIsOn = carStatus->getCtrlIsOn();
   goStatus = carStatus->carStatus();
   map = carStatus->getMap();
   // int pump = carStatus->getPump();

   QByteArray toggleCAN;
   toggleCAN.resize(8);
   qDebug() << "Current Status is " << goStatus << " Map is: " << map;
// NON Serve lo stato all'ECU controllare meglio, settare per Telemetria
   switch (goStatus) {
      case CAR_STATUS_STOP:
         toggleCAN[0] = 0x07;
         break;
      case CAR_STATUS_SETUP:
         toggleCAN[0] = 0x05;
         break;
      case CAR_STATUS_RUN:
         toggleCAN[0] = 0x06;
         break;
      case CAR_STATUS_IDLE:
         toggleCAN[0] = 0x16;      
         break;
      default:
         break;
   }

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

   sendCanMessage(STEERING_WHEEL_ID, toggleCAN);

}
// From TabInvertes ask if Inverter are active
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

// From TabSensor ask to calibrate pedals and steer 
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

}

// Set Id and Payload for Can Messages
void Canbus::sendCanMessage(int id, QByteArray message) {
   QCanBusFrame frame;
   frame.setFrameId(id);
   frame.setPayload(message);
   if(message[0] == 101) { qDebug() << frame.toString();}
   device->writeFrame(frame);
}

// Read Can-Bus
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

// Main Switch for Can Message
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

         if (msg.at(0) == 0x02){

            carStatus->setBrake(msg.at(1));
            // qDebug() << "------>Brake received" << msg.at(1);
         
         }else if(msg.at(0) == 0x01){//0x01 probabilmente
            
            carStatus->setThrottle(msg.at(1));
         }
      break;

      case ENCODERS: // 0xD0

         if(msg.at(0) == 0x06){
            carStatus->setSpeed(msg.at(1),msg.at(2));
         }else if(msg.at(0) == 8){
            carStatus->setKm(msg.at(1),msg.at(2));
         }

      break;

      case GET_ACTUATORS_RANGE_ACK:
         switch (msg.at(0)) {
            case 0:
               if (msg.at(1) == 0){
                  //APPS min
                  // qDebug() << "ACTUATORS_RANGE_ACK for APPS min";

                  m_actuatorRangePendingFlag = 3;
                  // qDebug() << "DONE APPS MIN now press A for MAX";
                  emit actuatorRangePendingFlagCleared();
               }
               else if (msg.at(1) == 1){
                  //APPS max
                  // qDebug() << "ACTUATORS_RANGE_ACK for APPS max";

                  m_actuatorRangePendingFlag = 0;
                  // qDebug() << "DONE APPS MAX now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
            break;

            case 1:
               if (msg.at(1) == 0){
                  //BSE min
                  // qDebug() << "ACTUATORS_RANGE_ACK for BSE min";

                  m_actuatorRangePendingFlag = 6;
                  // qDebug() << "DONE BSE MIN now press A for MAX";
                  emit actuatorRangePendingFlagCleared();
               }
               else if (msg.at(1) == 1){
                  //BSE max
                  // qDebug() << "ACTUATORS_RANGE_ACK for BSE max";
                  m_actuatorRangePendingFlag = 0;
                  // qDebug() << "DONE BSE MAX now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
            break;

            case 2:
               if (msg.at(1) == 0){
                  //STEER min
                  // qDebug() << "ACTUATORS_RANGE_ACK for STEER LEFT";
                  m_actuatorRangePendingFlag = 9;
                  // qDebug() << "DONE STEER LEFT now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
               else if (msg.at(1) == 1){
                  //STEER max
                  // qDebug() << "ACTUATORS_RANGE_ACK for STEER RIGHT";
                  m_actuatorRangePendingFlag = 0;
                  // qDebug() << "DONE STEER RIGHT now press Q";
                  emit actuatorRangePendingFlagCleared();
               }
            break;
      }
      break;

      case ECU_MSG:
      if(msg.at(0) == ECU_ERRORS){

         // -1 = 255 e -128 = 128, ovvero se tutti i bit sono a 1. Usate il qDebug sopra per scoprire il vostro valore magico
         //if((int)msg.at(1) == -1 && (int)msg.at(2) >= -128 && (int)msg.at(2) <= -1) // -1 = 255 e -128 = 128, ovvero se tutti i bit sono a 1. Usate il qDebug sopra per scoprire il vostro valore magico

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
            // qDebug() << "Error is 0" << (int)msg.at(1);
            carStatus->setError(0);
         }else{
            carStatus->setError(1);
            // qDebug() << "Error is 1" << (int)msg.at(1);
         }

         if((int)msg.at(2) <= 0){
            // qDebug() << "Warning is 0" << (int)msg.at(2);
            carStatus->setWarning(0);
         }else{
            carStatus->setWarning(1);
            // qDebug() << "Warning is 1" << (int)msg.at(2);
         }

      } else if(msg.at(0) == ECU_INV_LEFT){
         QString oldStatus = carStatus->HVStatus();
         carStatus->setHVStatus(oldStatus.mid(0,1).toInt(), 1, oldStatus.mid(2,1).toInt());
         // qDebug() << "Ricevuto Stato INV LEFT" << oldStatus.mid(0,1).toInt();
         // qDebug() << oldStatus;
         carStatus->setSteeringWheelPopup('1', '0', "L INV ON");
      } else if(msg.at(0) == ECU_INV_RIGHT){
         QString oldStatus = carStatus->HVStatus();
         carStatus->setHVStatus(oldStatus.mid(0,1).toInt(),oldStatus.mid(1,1).toInt(), 1);
         // qDebug() << "Ricevuto Stato INV RIGHT" << oldStatus.mid(1,1).toInt();
         // qDebug() << oldStatus;
         carStatus->setSteeringWheelPopup('1', '0', "R INV ON");
      } else if(msg.at(0) == 0x03){

         //entro in start

         ctrlIsEnabled = carStatus->getCtrlIsEnabled();
         ctrlIsOn = carStatus->getCtrlIsOn();
         goStatus = carStatus->carStatus();
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
            // per sicurezza, così in teoria dovrebbero già essere spenti
            carStatus->stopMessage(2);

            carStatus->setCarStatus(ctrlIsEnabled,
               ctrlIsOn,
               driveModeEnabled,
               0,
               0);

            carStatus->setSteeringWheelPopup('1', '0', "IDLE");

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
               
               carStatus->setSteeringWheelPopup('1', 'G', "GO");
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

               carStatus->setSteeringWheelPopup('1', 'Y', "SET UP");
               
         } else if(msg.at(0) == ECU_INV_LEFT_STOP){
            carStatus -> stopMessage(0);
         }else if(msg.at(0) == ECU_INV_RIGHT_STOP){
            carStatus -> stopMessage(1);
         }

      break;

      case BMS_ID:

         carStatus->setHVStatus( (uint8_t)msg.at(0),
                                 (uint8_t)msg.at(1),
                                 (uint8_t)msg.at(2),
                                 (uint8_t)msg.at(3),
                                 (uint8_t)msg.at(4),
                                 (uint8_t)msg.at(5),
                                 (uint8_t)msg.at(6),
                                 (uint8_t)msg.at(7));
      break;

      case LV_ID:
         // 0xFF->0x01-dataV-dataV-dataT-dataT-SCS 
         carStatus->setLVStatus( (uint8_t)msg.at(0),
                                 (uint8_t)msg.at(2));
     
      break;

// non me lo manda quello stronzo di bonneee
      case BMS_STATUS_ID:

         if (msg.at(3) == 0x2A) {
            
            //carStatus->setTemperature(msg.at(4));
            qDebug() << "Actually setTemperature is not used, to enable it remove comments";

         }

         if (msg.at(3) == 0xF) {
            
            //carStatus->setStateOfCharge(msg.at(4));
            qDebug() << "Actually setStateOfCharge is not used, to enable it remove comments";
         
         }
      break;

      // NON FUNZIONA BISOGNA rimuovere
      case GET_STEER_STATUS:
         
         carStatus->setSTEERStatus(msg.at(0));
      
      break;

      // NON FUNZIONA BISOGNA rimuovere
      case GET_APPS_BSE_STATUS:
      
         carStatus->setAPPSBSEStatus(msg.at(0),msg.at(2));
      
      break;

      case TELEMETRY:
         if(msg.at(0) == 0x65){
            carStatus -> setTelemetryStatus(msg.at(1), msg.at(2), msg.at(3));
            qDebug() << " 0x65 ";
         }
         if(msg.at(0) == 0x01) {
            //Marker
         }
      break;

   };
}

// Destroy, BOOM!
Canbus::~Canbus() {
   qDebug() << "Closing CAN...";
}
