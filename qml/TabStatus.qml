import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
   id: root
   property var btnClickable: true
   property var isStarted: false
   property var isStopped: true
   property var canstatus: CarStatus.CANStatus
   property var ledStates: ['OK', 'NO', 'DEFAULT']
   property var canLeds: [
   ["InvRight", 'CAN_DEFAULT'],
   ["InvLeft", 'CAN_DEFAULT'],
   ["STMFront", 'CAN_DEFAULT'],
   ["STMCentral", 'CAN_DEFAULT'],
   ["STMPedals", 'CAN_DEFAULT'],
   ["STMRear", 'CAN_DEFAULT'],
   ["BMS HV", 'CAN_DEFAULT'],
   ["BMS LV", 'CAN_DEFAULT'],
   ]

   onCanstatusChanged: {
      // console.log("Cambiato il CAN Status da Centralina");
      var newCanLeds = canLeds;

      for (var i=0; i < canstatus.length; i++) {
         newCanLeds[i][1] = ledStates[canstatus[i]];
      }

      canLeds = newCanLeds;
   }

   function connect() {
      mainwindow.btnClicked.connect(btnClickedHandler);
   }

   function disconnect() {
      mainwindow.btnClicked.disconnect(btnClickedHandler);
   }

   function btnClickedHandler(btnID) {
       tabView.stepIntoTab = true;
      if (btnID == 0) {
         //tabView.stepIntoTab = false;
         //btnClickable = false;
         mainwindow.menu.popupStatic.start();
      }
      if (btnID == 1) {
          CAN.askSetupOrIdle(1);
          console.log("Asking to go from IDLE to Setup");
          //isStarted = true;
         // Step into this tab and change the behaviour of btnID
         //if (!isStarted) {
            // Set ok to the update!
            //isStarted = true;
            //console.log("Asking to go from Idle to Setup");
            //CAN.checkCANCommunication(true);
             //CAN.askSetupOrIdle(1);
         //}else{
            //CarStatus.toggleCarStatus();
         //}

         // Set the button again to be not clickable
         //btnClickable = false;

         // Restore Button 0 initial handler
         //tabView.stepIntoTab = false;
      }

      if (btnID == 2) {
         if (!tabView.stepIntoTab) {
            // Set the button clickable
            //btnClickable = true;

            // Prevent the button 0 to switch to Racing Page!
            tabView.stepIntoTab = true;

         } else {
            console.log("Asking to go from Setup to Idle");
            //CAN.checkCANCommunication(false);
            // CarStatus.stopMessage(2);
            CAN.askSetupOrIdle(0);

         }
      }
      if (btnID == 3){
         CAN.sendMarker();
      }

      tabView.stepIntoTab = false;
   }

   Rectangle {
      id: status
      // color: menu.color
      color: "black"
      anchors.fill: parent

      GridLayout {
         id: grid1
         columns: 2
         rows: 4
         anchors.fill: parent
         columnSpacing: -15
         rowSpacing: -20

         Repeater {
            model: canLeds
            delegate: CANStatusLED {
               text: modelData[0]
               state: modelData[1]
               Layout.preferredWidth: status.width * 0.69
               Layout.preferredHeight: status.height / 5
            }
         }


         Rectangle {
            Layout.preferredWidth: status.width * 0.33
            Layout.preferredHeight: status.height / 7
            state: root.btnClickable & !isStarted ? 'SELECTED' : 'IDLE'
            radius: 20
            color: "green"
            Text {
               text: "START"
               color: "lightgray"
               anchors.centerIn: parent
               font.pixelSize: 15
               font.family: labelFont.name
            }
         }

         Rectangle {
            id: ask
            Layout.preferredWidth: status.width * 0.33
            Layout.preferredHeight: status.height / 7
            state: root.btnClickable ? 'SELECTED' : 'IDLE'
            radius: 20
            color: "red"
            Text {
               text: "STOP"
               color: "lightgray"
               anchors.centerIn: parent
               font.pixelSize: 15
               font.family: labelFont.name
            }
         }
      }
   }
}
