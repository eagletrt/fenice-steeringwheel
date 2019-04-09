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
   property variant throttlenames : ["../img/t1.png","../img/t2.png","../img/t3.png","../img/t4.png","../img/t5.png","../img/t6.png",
   "../img/t7.png","../img/t8.png","../img/t9.png","../img/t10.png"];
   property variant brakenames : ["../img/b1.png","../img/b2.png","../img/b3.png","../img/b4.png","../img/b5.png","../img/b6.png",
   "../img/b7.png","../img/b8.png","../img/b9.png","../img/b10.png"];
   property int brakeidx :0;
   property int throttleidx : 0;

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
         brakeidx = brakeValore/10;
         //console.log("Brake Changed: " + brakeValore);
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
