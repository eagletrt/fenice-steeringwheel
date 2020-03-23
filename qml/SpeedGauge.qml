import QtQuick 2.7

Rectangle {

   property int hvTemp: CarStatus.hvTemp;
   property int hvVolt: CarStatus.hvVolt;
   property int lvTemp: CarStatus.lvTemp;
   property int lvVolt: CarStatus.lvVolt;
   
   property int velocity: CarStatus.velocity
   property int speed: CarStatus.speed;
   property int km: CarStatus.km;

   property int invSxTemp: CarStatus.invSxTemp;
   property int invDxTemp: CarStatus.invDxTemp;

   property variant throttlenames : ["../img/t1.png","../img/t2.png","../img/t3.png","../img/t4.png","../img/t5.png","../img/t6.png",
   "../img/t7.png","../img/t8.png","../img/t9.png","../img/t10.png"];

   property variant brakenames : ["../img/b1.png","../img/b2.png","../img/b3.png","../img/b4.png","../img/b5.png","../img/b6.png",
   "../img/b7.png","../img/b8.png","../img/b9.png","../img/b10.png"];
   
   property int brakeidx :0;
   property int throttleidx : 0;

   color: "transparent"

   Text {
      id: textVelocity
      text: velocity + " KW"
      font.family: valueFont.name;
      font.pointSize: 10
      y: 260
      x: 180
      width:200
      horizontalAlignment: Text.AlignHCenter;
      color: "lightgray"
   }

   Text {
      id: textKm
      text: km + " m"
      font.family: valueFont.name;
      font.pointSize: 10
      y: 260
      x: 240
      width:200
      horizontalAlignment: Text.AlignHCenter;
      color: "lightgray"
   }

   Text {
      id: textInvSxTemp
      text: invSxTemp / 10.0 + "°C"
      font.family: valueFont.name;
      font.pointSize: 10
      x: 10
      y: 160
      color: "lightgray"
   }

   Text {
      id: textInvDxTemp
      text: invDxTemp / 10 + "°C"
      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 10
      font.family: valueFont.name;
      x: 610
      y: 160
      width: 70
      color: "lightgray"
   }

   Text {
      id: texthvTemp

      // property int hvTemp: CarStatus.hvTemp

      text: hvTemp/10 +  " °C"

      font.family: valueFont.name;
      font.pointSize: 10
      x: 10
      y: 220
      color: "lightgray"
   }

   Text {
      id: texthvVolt

      // property int hvVolt: CarStatus.hvVolt / 10
      
      text: hvVolt/10 +  " V"

      font.family: valueFont.name;
      font.pointSize: 10
      x: 10
      y: 260
      color: "lightgray"
   }

   Text {
      id: textlvTemp

      // property int lvTemp: CarStatus.lvTemp

      text: lvTemp/5 + " °C"

      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 10
      font.family: valueFont.name;
      x: 610
      y: 220
      width: 70
      color: "lightgray"
   }

   Text {
      id: textlvVolt

      // property int lvVolt: CarStatus.lvVolt 

      text: lvVolt/10 + " V"
      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 10
      font.family: valueFont.name;
      x: 610
      y: 260
      width: 70
      color: "lightgray"
   }

   Item{
      property var throttleVal: CarStatus.throttleVal;
      property int throttleValore: throttleVal;

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -310
      anchors.horizontalCenterOffset: -430

      onThrottleValChanged: function(){
         throttleValore = CarStatus.throttleVal
         throttleidx = throttleValore/10
      }
      Repeater{
         model: throttleidx
         Image{
            id: throttles
            source: throttlenames[index]
            opacity: 1
         }
      }
   }

   Text {
      id: carSpeed
      text: speed
      font.pointSize: 55
      font.family: valueFont.name;
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -15
      color: "lightgray"
   }

   Text {
      text: "km/h"
      font.family: labelFont.name;
      font.pointSize: 8
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: 48
      color: "lightgray"
   }
   Item{
      property var brakeVal: CarStatus.brakeVal;
      property int brakeValore: brakeVal;

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -295
      anchors.horizontalCenterOffset: -380

      onBrakeValChanged: function(){
         brakeValore = CarStatus.brakeVal;
         brakeidx = brakeValore/10;
         //console.log(brakeidx)
       }
       Repeater{
         model: brakeidx
         Image{
           id: breaks
           source: brakenames[index]
           opacity: 1
         }
      }
   }
}

 