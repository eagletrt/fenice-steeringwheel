import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQml.Models 2.2

Rectangle {
   id: root
   color: "#000000"
   anchors.fill: parent
   FontLoader {id:blackops; source: "../lib/blops.ttf"}

   property var appsStatus: CarStatus.APPSStatus
   property var bseStatus: CarStatus.BSEStatus
   property var steerStatus: CarStatus.STEERStatus
   property var ledStates: ['DEFAULT', 'NO'];

   property var choiceButtonSelected: 0
   property var mBtnSetText: "SET"
   property var mHelpSetText: "Set Actuators [MIN,MAX]"

   property var setPendingFlag: CAN.actuatorRangePendingFlag

   ListModel {
      id: sensors

      ListElement {
         mText: "APPS"
         mColor: "green"
         mValue: 50
         mSelected: 0
      }

      ListElement {
         mText: "BSE"
         mColor: "red"
         mValue: 60
         mSelected: 0
      }

      ListElement {
         mText: "STEER"
         mColor: "grey"
         mValue: 20
         mSelected: 0
      }

   }

   onSetPendingFlagChanged: function(){
      switch(setPendingFlag){
      case 0:
         root.mBtnSetText = "SET MIN";
         root.mHelpSetText = "Set Actuators";
         break;
      case 1:
         root.mBtnSetText = "SETTING...";
         root.mHelpSetText = "APPS MIN ACK";
         break;
      case 2:
         root.mBtnSetText = "SETTING...";
         root.mHelpSetText = "APPS MAX ACK";
         break;
      case 3:
         root.mBtnSetText = "SET MAX";
         root.mHelpSetText = "DONE APPS";
         choiceButtonSelected = 0;
         break;
      case 4:
         root.mBtnSetText = "SETTING...";
         root.mHelpSetText = "BSE MIN ACK";
         break;
      case 5:
         root.mBtnSetText = "SETTING...";
         root.mHelpSetText = "BSE MAX ACK";
         break;
      case 6:
         root.mBtnSetText = "SET MAX";
         root.mHelpSetText = "DONE BSE";
         choiceButtonSelected = 0;
         break;
      case 7:
         root.mBtnSetText = "SETTING...";
         root.mHelpSetText = "STEER LEFT ACK";
         break;
      case 8:
         root.mBtnSetText = "SETTING...";
         root.mHelpSetText = "STEER RIGHT ACK";
         break;
      case 9:
         root.mBtnSetText = "SET MAX";
         root.mHelpSetText = "DONE STEER";
         choiceButtonSelected = 0;
         break;
      }
   }

   property var btnClickable: false
   property var isStarted: false
   property var sensorSelectedIndex: -1

   function connect() {
      console.log("Tab connessa - Sensors");
      menu.btnClicked.connect(btnClickedHandler);
   }

   function disconnect() {
      console.log("Tab disconnessa - Sensors");
      menu.btnClicked.disconnect(btnClickedHandler);

   }

   function unSelectSensors() {
      if (sensorSelectedIndex != -1) {
         sensors.setProperty(sensorSelectedIndex, "mSelected", 0);
      }
   }

   function selectSensor(index) {
      if (sensorSelectedIndex != -1) {
         sensors.setProperty(sensorSelectedIndex, "mSelected", 0);
      }

      index = index % 3;

      sensors.setProperty(index, "mSelected", 1);

      sensorSelectedIndex = index;
   }

   function btnClickedHandler(btnID) {
      if (btnID == 0) {
         if (tabView.stepIntoTab && !choiceButtonSelected) {
            // We are into the tab, get out!
            btnClickable = false;
            isStarted = false;

            // Remove highlight from current selected sensor item
            unSelectSensors();
            mainwindow.canSwitchPage = true;
            tabView.stepIntoTab = false;
         }
         //se non arriva l'ack non esce
         if (choiceButtonSelected) { //&& !setPendingFlag
            choiceButtonSelected = 0;
         }
         CAN.setActuatorsRange(777,777);

      }

      if (btnID == 1) {
         if (tabView.stepIntoTab && !choiceButtonSelected)  {
            // Enable buttons for current sensors!
            choiceButtonSelected = 1
            //root.mBtnSetText = "Set...";
            switch(setPendingFlag){
            case 0:
               CAN.setActuatorsRange(sensorSelectedIndex,0);
               break;
            case 3:
               CAN.setActuatorsRange(sensorSelectedIndex,1);
               break;
            case 6:
               CAN.setActuatorsRange(sensorSelectedIndex,1);
               break;
            case 9:
               CAN.setActuatorsRange(sensorSelectedIndex,1);
               break;
            }
         }
      }

      if (btnID == 2) {
         // Step into this tab and change the behaviour of btnID
         if (!tabView.stepIntoTab) {
            // Set the button clickable
            btnClickable = true;

            // Select the first entry of the SensorsList
            selectSensor(0);
            // Prevent the button 0 to switch to Racing Page!
            tabView.stepIntoTab = true;
            mainwindow.canSwitchPage = false;

         } else {
            if (!choiceButtonSelected) {
               // Loop through sensors
               selectSensor(sensorSelectedIndex + 1);
               //console.log(sensorSelectedIndex+" D2");
            }
         }
      }
   }

   ColumnLayout {
      anchors.fill: parent
      spacing: 0

      ListView {
         id: sensorListView
         width: parent.width
         Layout.preferredHeight: parent.height * 0.75
         model: sensors
         delegate: SensorStatus {
            text: mText
            barColor: mColor
            barValue: mValue
            selected: mSelected
            height: sensorListView.height / 3
            width: parent.width
         }
      }

      Rectangle {
         Layout.fillWidth: true
         Layout.preferredHeight: parent.height / 4
         color: menu.color

         GridLayout {
            anchors.fill: parent
            rows: 1
            columns: 2

            Text {
               text: mHelpSetText
               Layout.fillHeight: true
               Layout.preferredWidth: parent.width * 0.60
               color: "lightgray"
               verticalAlignment: Text.AlignVCenter
               horizontalAlignment: Text.AlignHCenter
               font.family: blackops.name;
               font.pointSize: 7
            }

            Item {
               Layout.fillHeight: true
               Layout.fillWidth: true
               width: 50
               ChoiceButton {
                  width: 150
                  height: 40
                  btnColor: "green"
                  btnText: mBtnSetText
                  selected: choiceButtonSelected && (setPendingFlag>0)
               }
            }
         }
      }
   }
}
