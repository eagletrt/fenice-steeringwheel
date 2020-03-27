import QtQuick 2.0

Item{
   id: statusframe

   property var carStatus : CarStatus.carStatus;
   property var telemetryenabledstatus: CarStatus.TelemetryEnabledStatus;
   property int statusID: carStatus;

   onCarStatusChanged: function() {
      statusID = CarStatus.carStatus;
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
            telemetryAnimation.stop();
            telemetry.opacity = 0;
            telemetry_na.opacity = 1;
            break;
         case 1:
            telemetryAnimation.stop();
            telemetry.opacity = 1;
            telemetry_na.opacity = 0;         
            break;
         case 2:
            telemetry_na.opacity = 0; //for avoiding a bug passing from 1 to 2
            telemetryAnimation.start();
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
      id: idle_na
      objectName: "idle-na"
      source: "../img/idle-na.png"
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
      id: telemetry_na
      objectName: "telemetry_na"
      source: "../img/telemetry-na.png"
      opacity: 1
   }

   Image {
      id: telemetry
      objectName: "telemetry"
      source: "../img/telemetry.png"
      opacity: 1
   }

    SequentialAnimation {
         id: telemetryAnimation
         running: false
         loops: Animation.Infinite
         PropertyAnimation {
            id: telemetryEnabled; 
            target: telemetry; 
            properties: "opacity"; 
            from: 0;
            to: 1; 
            duration: 700
         }
         PropertyAnimation {
            id: telemetryDisabled; 
            target: telemetry; 
            properties: "opacity"; 
            from: 1;
            to: 0; 
            duration: 500
         }
    }

}
