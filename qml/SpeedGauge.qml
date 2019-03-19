import QtQuick 2.7

Rectangle {

   FontLoader {id:blackops; source: "../lib/blops.ttf"}

   property int hvTemp: CarStatus.hvTemp;
   property int hvVolt: CarStatus.hvVolt;
   property int lvTemp: CarStatus.lvTemp;
   property int lvVolt: CarStatus.lvVolt;

   property int speed: CarStatus.speed;
   property int invSxTemp: CarStatus.invSxTemp;
   property int invDxTemp: CarStatus.invDxTemp;

   property int velocity: CarStatus.velocity

   color: "transparent"

   Text {
      id: carSpeed
      text: speed + " KMH"
      font.family: blackops.name;
      font.pointSize: 7
      y: 130
      x: 85
      width:200
      horizontalAlignment: Text.AlignHCenter;
      color: "lightgray"
   }

   Text {
      id: textInvSxTemp
      text: invSxTemp / 10.0 + "°C"
      font.family: blackops.name;
      font.pointSize: 7
      y: 60
      color: "lightgray"
   }

   Text {
      id: textInvDxTemp
      text: invDxTemp / 10 + "°C"
      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 7
      font.family: blackops.name;
      x: 310
      y: 60
      width: 70
      color: "lightgray"
   }

   Text {
      id: texthvTemp
      text: CarStatus.hvTemp / 10 +  " °C"
      font.family: blackops.name;
      font.pointSize: 7
      y: 100
      color: "lightgray"
   }

   Text {
      id: texthvVolt
      text: CarStatus.hvVolt / 10 +  " V"
      font.family: blackops.name;
      font.pointSize: 7
      y: 120
      color: "lightgray"
   }

   Text {
      id: textlvTemp
      text: CarStatus.lvTemp / 5 + " °C"

      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 7
      font.family: blackops.name;
      x: 310
      y: 100
      width: 70
      color: "lightgray"
   }

   Text {
      id: textlvVolt
      text: CarStatus.lvVolt / 10 + " V"
      horizontalAlignment: Text.AlignLeft;
      font.pointSize: 7
      font.family: blackops.name;
      x: 310
      y: 120
      width: 70
      color: "lightgray"
   }

   Item{
      property var throttleVal: CarStatus.throttleVal;
      property int throttleValore: throttleVal;

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -130
      anchors.horizontalCenterOffset: -172

      onThrottleValChanged: function(){
         throttleValore = CarStatus.throttleVal;
         if(throttleValore < 10){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 0;
               t6.opacity = 0;
               t5.opacity = 0;
               t4.opacity = 0;
               t3.opacity = 0;
               t2.opacity = 0;
               t1.opacity = 0;
         }else if(throttleValore>=10 && throttleValore<20){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 0;
               t6.opacity = 0;
               t5.opacity = 0;
               t4.opacity = 0;
               t3.opacity = 0;
               t2.opacity = 0;
               t1.opacity = 1;
         }else if(throttleValore>=20 && throttleValore<30){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 0;
               t6.opacity = 0;
               t5.opacity = 0;
               t4.opacity = 0;
               t3.opacity = 0;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=30 && throttleValore<40){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 0;
               t6.opacity = 0;
               t5.opacity = 0;
               t4.opacity = 0;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=40 && throttleValore<50){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 0;
               t6.opacity = 0;
               t5.opacity = 0;
               t4.opacity = 1;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=50 && throttleValore<60){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 0;
               t6.opacity = 0;
               t5.opacity = 1;
               t4.opacity = 1;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=60 && throttleValore<70){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 0;
               t6.opacity = 1;
               t5.opacity = 1;
               t4.opacity = 1;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=70 && throttleValore<80){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 0;
               t7.opacity = 1;
               t6.opacity = 1;
               t5.opacity = 1;
               t4.opacity = 1;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=80 && throttleValore<90){
               t10.opacity = 0;
               t9.opacity = 0;
               t8.opacity = 1;
               t7.opacity = 1;
               t6.opacity = 1;
               t5.opacity = 1;
               t4.opacity = 1;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=90 && throttleValore<100){
               t10.opacity = 0;
               t9.opacity = 1;
               t8.opacity = 1;
               t7.opacity = 1;
               t6.opacity = 1;
               t5.opacity = 1;
               t4.opacity = 1;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }else if(throttleValore>=100){
               t10.opacity = 1;
               t9.opacity = 1;
               t8.opacity = 1;
               t7.opacity = 1;
               t6.opacity = 1;
               t5.opacity = 1;
               t4.opacity = 1;
               t3.opacity = 1;
               t2.opacity = 1;
               t1.opacity = 1;
         }
      }

      Image {
         id: t1
         objectName: "t1"
         source: "../img/t1.png"
         opacity: 1
      }

      Image {
         id: t2
         objectName: "t2"
         source: "../img/t2.png"
         opacity: 1
      }

      Image {
         id: t3
         objectName: "t3"
         source: "../img/t3.png"
         opacity: 1
      }

      Image {
         id: t4
         objectName: "t4"
         source: "../img/t4.png"
         opacity: 1
      }

      Image {
         id: t5
         objectName: "t5"
         source: "../img/t5.png"
         opacity: 1
      }

      Image {
         id: t6
         objectName: "t6"
         source: "../img/t6.png"
         opacity: 1
      }

      Image {
         id: t7
         objectName: "t7"
         source: "../img/t7.png"
         opacity: 1
      }

      Image {
         id: t8
         objectName: "t8"
         source: "../img/t8.png"
         opacity: 1
      }

      Image {
         id: t9
         objectName: "t9"
         source: "../img/t9.png"
         opacity: 1
      }

      Image {
         id: t10
         objectName: "t10"
         source: "../img/t10.png"
         opacity: 1
      }

   }

   Text {
      id: textVelocity
      text: velocity
      font.pointSize: 35
      font.family: blackops.name;
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -15
      color: "lightgray"
   }

   Text {
      text: "kw"
      font.family: blackops.name;
      font.pointSize: 5
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: 28
      color: "lightgray"
   }

   Item{
      property var brakeVal: CarStatus.brakeVal;
      property int brakeValore: brakeVal;

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: -119
      anchors.horizontalCenterOffset: -207

      onBrakeValChanged: function(){
         brakeValore = CarStatus.brakeVal;
         //console.log("Brake Changed: " + brakeValore);
         if(brakeValore == 0){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 0;
               b6.opacity = 0;
               b5.opacity = 0;
               b4.opacity = 0;
               b3.opacity = 0;
               b2.opacity = 0;
               b1.opacity = 0;
         }else if(brakeValore>=10 && brakeValore<20){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 0;
               b6.opacity = 0;
               b5.opacity = 0;
               b4.opacity = 0;
               b3.opacity = 0;
               b2.opacity = 0;
               b1.opacity = 1;
         }else if(brakeValore>=20 && brakeValore<30){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 0;
               b6.opacity = 0;
               b5.opacity = 0;
               b4.opacity = 0;
               b3.opacity = 0;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore>=30 && brakeValore<40){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 0;
               b6.opacity = 0;
               b5.opacity = 0;
               b4.opacity = 0;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore>=40 && brakeValore<50){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 0;
               b6.opacity = 0;
               b5.opacity = 0;
               b4.opacity = 1;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore>=50 && brakeValore<60){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 0;
               b6.opacity = 0;
               b5.opacity = 1;
               b4.opacity = 1;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore>=60 && brakeValore<70){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 0;
               b6.opacity = 1;
               b5.opacity = 1;
               b4.opacity = 1;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore>=70 && brakeValore<80){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 0;
               b7.opacity = 1;
               b6.opacity = 1;
               b5.opacity = 1;
               b4.opacity = 1;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore>=80 && brakeValore<90){
               b10.opacity = 0;
               b9.opacity = 0;
               b8.opacity = 1;
               b7.opacity = 1;
               b6.opacity = 1;
               b5.opacity = 1;
               b4.opacity = 1;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore>=90 && brakeValore<100){
               b10.opacity = 0;
               b9.opacity = 1;
               b8.opacity = 1;
               b7.opacity = 1;
               b6.opacity = 1;
               b5.opacity = 1;
               b4.opacity = 1;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }else if(brakeValore==1){
               b10.opacity = 1;
               b9.opacity = 1;
               b8.opacity = 1;
               b7.opacity = 1;
               b6.opacity = 1;
               b5.opacity = 1;
               b4.opacity = 1;
               b3.opacity = 1;
               b2.opacity = 1;
               b1.opacity = 1;
         }
      }

      Image {
         id: b1
         objectName: "b1"
         source: "../img/b1.png"
         opacity: 1
      }

      Image {
         id: b2
         objectName: "b2"
         source: "../img/b2.png"
         opacity: 1
      }

      Image {
         id: b3
         objectName: "b3"
         source: "../img/b3.png"
         opacity: 1
      }

      Image {
         id: b4
         objectName: "b4"
         source: "../img/b4.png"
         opacity: 1
      }

      Image {
         id: b5
         objectName: "b5"
         source: "../img/b5.png"
         opacity: 1
      }

      Image {
         id: b6
         objectName: "b6"
         source: "../img/b6.png"
         opacity: 1
      }

      Image {
         id: b7
         objectName: "b7"
         source: "../img/b7.png"
         opacity: 1
      }

      Image {
         id: b8
         objectName: "b8"
         source: "../img/b8.png"
         opacity: 1
      }

      Image {
         id: b9
         objectName: "b9"
         source: "../img/b9.png"
         opacity: 1
      }

      Image {
         id: b10
         objectName: "b10"
         source: "../img/b10.png"
         opacity: 1
      }

   }
}
