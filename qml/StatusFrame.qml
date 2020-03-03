import QtQuick 2.0

Item{
   id: statusframe

   property var carStatus : CarStatus.carStatus;
   property var telemetryenabledstatus: CarStatus.TelemetryEnabledStatus;
   property int statusID: carStatus;

   onCarStatusChanged: function() {
      statusID = CarStatus.carStatus;
      // console.log("Car Status Changed: " + statusID);
      switch (statusID){
         case 0:
            idle.opacity = 1;
            run.opacity = 0;
            setup.opacity = 0;
            stop.opacity = 0;
            break;
         case 1:
            idle.opacity = 0;
            run.opacity = 0;
            setup.opacity = 1;
            stop.opacity = 0;
            break;
         case 2:
            idle.opacity = 0;
            run.opacity = 1;
            setup.opacity = 0;
            stop.opacity = 0;
            break;
         case 3:
            idle.opacity = 0;
            run.opacity = 0;
            setup.opacity = 0;
            stop.opacity = 1;
            break;
      }
   }

   onTelemetryenabledstatusChanged: {  
      console.log(telemetryenabledstatus);
      switch(telemetryenabledstatus){
         case 0:
            radioAnimation.stop();
            radio.opacity = 0;
            radio_na.opacity = 1;
            break;
         case 1:
            radioAnimation.stop();
            radio.opacity = 1;
            radio_na.opacity = 0;         
            break;
         case 2:
            radio_na.opacity = 0; //for avoiding a bug passing from 1 to 2
            radioAnimation.start();
            break;         
      }
   }

   Image {
      id: idle
      objectName: "idle"
      source: "../img/idle.png"
      opacity: 1
   }

   Image {
      id: run
      objectName: "run"
      source: "../img/run.png"
      opacity: 0
   }

   Image {
      id: stop
      objectName: "stop"
      source: "../img/stop.png"
      opacity: 0
   }

   Image {
      id: setup
      objectName: "setup"
      source: "../img/setup.png"
      opacity: 0
   }

   Image {
      id: radio
      objectName: "radio"
      source: "../img/radio.png"
      opacity: 0
   } 

   Image {
      id: radio_na
      objectName: "radio_na"
      source: "../img/radio_na.png"
      opacity: 1
   }

    SequentialAnimation {
         id: radioAnimation
         running: false
         loops: Animation.Infinite
         PropertyAnimation {
            id: radioEnabled; 
            target: radio; 
            properties: "opacity"; 
            from: 0;
            to: 1; 
            duration: 1000
         }
         PropertyAnimation {
            id: radioDisabled; 
            target: radio; 
            properties: "opacity"; 
            from: 1;
            to: 0; 
            duration: 1000
         }
    }

}
