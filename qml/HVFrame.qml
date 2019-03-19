import QtQuick 2.0

Item{

   property var hvVolt : CarStatus.hvVolt;
   property int hvVal : hvVolt;

   onHvVoltChanged: function(){

      //console.log("car status: ",CarStatus.hvVolt);
      //console.log("hvVolt",hvVolt);
      hvVal = CarStatus.hvVolt / 10;
      //console.log("hvVal",hvVal);
      if(hvVal<340){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 0;
         hv10.opacity = 0;
         hv9.opacity = 0;
         hv8.opacity = 0;
         hv7.opacity = 0;
         hv6.opacity = 0;
         hv5.opacity = 0;
         hv4.opacity = 0;
         hv3.opacity = 0;
         hv2.opacity = 1;
      }else if(hvVal>=350 && hvVal<360){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 0;
         hv10.opacity = 0;
         hv9.opacity = 0;
         hv8.opacity = 0;
         hv7.opacity = 0;
         hv6.opacity = 0;
         hv5.opacity = 0;
         hv4.opacity = 0;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=360 && hvVal<370){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 0;
         hv10.opacity = 0;
         hv9.opacity = 0;
         hv8.opacity = 0;
         hv7.opacity = 0;
         hv6.opacity = 0;
         hv5.opacity = 0;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=370 && hvVal<380){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 0;
         hv10.opacity = 0;
         hv9.opacity = 0;
         hv8.opacity = 0;
         hv7.opacity = 0;
         hv6.opacity = 0;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=380 && hvVal<390){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 0;
         hv10.opacity = 0;
         hv9.opacity = 0;
         hv8.opacity = 0;
         hv7.opacity = 1;
         hv6.opacity = 1;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=390 && hvVal<400){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 0;
         hv10.opacity = 0;
         hv9.opacity = 1;
         hv8.opacity = 1;
         hv7.opacity = 1;
         hv6.opacity = 1;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=400 && hvVal<410){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 0;
         hv10.opacity = 1;
         hv9.opacity = 1;
         hv8.opacity = 1;
         hv7.opacity = 1;
         hv6.opacity = 1;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=410 && hvVal<420){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 0;
         hv11.opacity = 1;
         hv10.opacity = 1;
         hv9.opacity = 1;
         hv8.opacity = 1;
         hv7.opacity = 1;
         hv6.opacity = 1;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=420 && hvVal<430){
         hv14.opacity = 0;
         hv13.opacity = 0;
         hv12.opacity = 1;
         hv11.opacity = 1;
         hv10.opacity = 1;
         hv9.opacity = 1;
         hv8.opacity = 1;
         hv7.opacity = 1;
         hv6.opacity = 1;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=430 && hvVal<440){
         hv14.opacity = 0;
         hv13.opacity = 1;
         hv12.opacity = 1;
         hv11.opacity = 1;
         hv10.opacity = 1;
         hv9.opacity = 1;
         hv8.opacity = 1;
         hv7.opacity = 1;
         hv6.opacity = 1;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }else if(hvVal>=440){
         hv14.opacity = 1;
         hv13.opacity = 1;
         hv12.opacity = 1;
         hv11.opacity = 1;
         hv10.opacity = 1;
         hv9.opacity = 1;
         hv8.opacity = 1;
         hv7.opacity = 1;
         hv6.opacity = 1;
         hv5.opacity = 1;
         hv4.opacity = 1;
         hv3.opacity = 1;
         hv2.opacity = 1;
      }
   }

   Image {
      id: hv
      source: "../img/HV.png"
      opacity: 1
   }

   Image {
      id: hv0
      objectName: "hv0"
      source: "../img/hv0.png"
      opacity: 1
   }

   Image {
      id: hv1
      objectName: "hv1"
      source: "../img/hv1.png"
      opacity: 1
   }

   Image {
      id: hv2
      objectName: "hv2"
      source: "../img/hv2.png"
      opacity: 1
   }

   Image {
      id: hv3
      objectName: "hv3"
      source: "../img/hv3.png"
      opacity: 1
   }

   Image {
      id: hv4
      objectName: "hv4"
      source: "../img/hv4.png"
      opacity: 1
   }

   Image {
      id: hv5
      objectName: "hv5"
      source: "../img/hv5.png"
      opacity: 1
   }

   Image {
      id: hv6
      objectName: "hv6"
      source: "../img/hv6.png"
      opacity: 1
   }

   Image {
      id: hv7
      objectName: "hv7"
      source: "../img/hv7.png"
      opacity: 1
   }

   Image {
      id: hv8
      objectName: "hv8"
      source: "../img/hv8.png"
      opacity: 1
   }

   Image {
      id: hv9
      objectName: "hv9"
      source: "../img/hv9.png"
      opacity: 1
   }

   Image {
      id: hv10
      objectName: "hv10"
      source: "../img/hv10.png"
      opacity: 1
   }

   Image {
      id: hv11
      objectName: "hv11"
      source: "../img/hv11.png"
      opacity: 1
   }

   Image {
      id: hv12
      objectName: "hv12"
      source: "../img/hv12.png"
      opacity: 1
   }

   Image {
      id: hv13
      objectName: "hv13"
      source: "../img/hv13.png"
      opacity: 1
   }

   Image {
      id: hv14
      objectName: "hv14"
      source: "../img/hv14.png"
      opacity: 1
   }

}
