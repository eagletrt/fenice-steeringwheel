import QtQuick 2.0

Item{
   property var lvVolt : CarStatus.lvVolt;
   property int lvVal : lvVolt;
   property int lvCounter : lvVal;

   property variant lvnames : ["../img/lv3.png","../img/lv4.png","../img/lv5.png","../img/lv6.png","../img/lv7.png",
   "../img/lv8.png","../img/lv9.png","../img/lv10.png","../img/lv11.png","../img/lv12.png","../img/lv13.png"];//"../img/lv14.png"

   onLvVoltChanged: function(){
      lvCounter = CarStatus.lvVolt - 80;
      if(lvCounter < 0){
         lvVal = 0;
      }else{
         lvVal = Math.floor(lvCounter/10);
      }
   }

   Repeater{
      model: lvVal
      Image{
         id: lv
         source: lvnames[index]
         opacity: 1
      }
   }

   Image {
      id: lv
      source: "../img/LV.png"
      opacity: 1
   }

   Image {
      id: lv0
      objectName: "lv0"
      source: "../img/lv0.png"
      opacity: 1
   }

   Image {
      id: lv1
      objectName: "lv1"
      source: "../img/lv1.png"
      opacity: 1
   }

   Image {
      id: lv2
      objectName: "lv2"
      source: "../img/lv2.png"
      opacity: 1
   }

}
