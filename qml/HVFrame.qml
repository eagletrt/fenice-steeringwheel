import QtQuick 2.0

Item{

   property var hvVolt : CarStatus.hvVolt;
   property int hvVal : hvVolt;

   property variant hvnames : ["../img/hv3.png","../img/hv4.png","../img/hv5.png","../img/hv6.png","../img/hv7.png",
   "../img/hv8.png","../img/hv9.png","../img/hv10.png","../img/hv11.png","../img/hv12.png","../img/hv13.png","../img/hv14.png"];


   onHvVoltChanged: function(){

      //console.log("car status: ",CarStatus.hvVolt);
      //console.log("hvVolt",hvVolt);
      hvVal = CarStatus.hvVolt / 10;
      //console.log("hvVal",hvVal);
      hvVal = hvVal-340;
      if(hvVal<0)
       hvVal =0
      //console.log("lv "+lvVal)
      hvVal = Math.floor(hvVal/10);
}
      Repeater{
        model: hvVal
        Image{
          id: hv
          source: hvnames[index]
          opacity: 1
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


}
