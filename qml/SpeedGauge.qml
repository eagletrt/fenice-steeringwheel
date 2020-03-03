import QtQuick 2.7

Rectangle {

   FontLoader {id:blackops; source: "../lib/blops.ttf"}

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
      font.family: blackops.name;
      font.pointSize: 15
      y: 145
      x: 25
      width:200
      horizontalAlignment: Text.AlignHCenter;
      color: "lightgray"
   }

   Text {
      id: textKm
      text: km + " m"
      font.family: blackops.name;
      font.pointSize: 15
      y: 145
      x: 145
      width:200
      horizontalAlignment: Text.AlignHCenter;
      color: "lightgray"
   }

   Text {
      id: textInvSxTemp
      text: invSxTemp / 10.0 + "°C"
      font.family: blackops.name;
      font.pointSize: 15
      y: 80
      color: "lightgray"
   }

   Text {
      id: textInvDxTemp
      text: invDxTemp / 10 + "°C"
      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 15
      font.family: blackops.name;
      x: 305
      y: 80
      width: 70
      color: "lightgray"
   }

   Text {
      id: texthvTemp

      // property int hvTemp: CarStatus.hvTemp

      text: hvTemp/10 +  " °C"

      font.family: blackops.name;
      font.pointSize: 15
      y: 120
      color: "lightgray"
   }

   Text {
      id: texthvVolt

      // property int hvVolt: CarStatus.hvVolt / 10
      
      text: hvVolt/10 +  " V"

      font.family: blackops.name;
      font.pointSize: 15
      y: 140
      color: "lightgray"
   }

   Text {
      id: textlvTemp

      // property int lvTemp: CarStatus.lvTemp

      text: lvTemp/5 + " °C"

      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 15
      font.family: blackops.name;
      x: 305
      y: 120
      width: 70
      color: "lightgray"
   }

   Text {
      id: textlvVolt

      // property int lvVolt: CarStatus.lvVolt 

      text: lvVolt/10 + " V"
      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 15
      font.family: blackops.name;
      x: 305
      y: 140
      width: 70
      color: "lightgray"
   }

   Item{
      property var throttleVal: CarStatus.throttleVal;
      property int throttleValore: throttleVal;

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -140
      anchors.horizontalCenterOffset: -172

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
      font.pointSize: 85
      font.family: blackops.name;
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -22
      color: "lightgray"
   }

   Text {
      text: "km/h"
      font.family: blackops.name;
      font.pointSize: 12
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: 18
      color: "lightgray"
   }
   Item{
      property var brakeVal: CarStatus.brakeVal;
      property int brakeValore: brakeVal;

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -129
      anchors.horizontalCenterOffset: -207

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

 