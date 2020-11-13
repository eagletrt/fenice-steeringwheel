import QtQuick 2.0

Item {
    /*
   Il valore che viene preso da cpp + già diviso 1000
   probabilmente basterà dividerlo per
   esempio:
         340 < x < 440
      4200 volt -> 4200*1000 = 4200 000

*/

    property var hvVolt: CarStatus.hvVolt
    property int hvVal: hvVolt
    property int hvCounter: hvVal
    property variant hvnames: ["qrc:///qml/img/hv3.png", "qrc:///qml/img/hv4.png", "qrc:///qml/img/hv5.png", "qrc:///qml/img/hv6.png", "qrc:///qml/img/hv7.png", "qrc:///qml/img/hv8.png", "qrc:///qml/img/hv9.png", "qrc:///qml/img/hv10.png", "qrc:///qml/img/hv11.png", "qrc:///qml/img/hv12.png", "qrc:///qml/img/hv13.png", "qrc:///qml/img/hv14.png", "qrc:///qml/img/hv15.png"] //"qrc:///qml/img/hv16.png"

    onHvVoltChanged: function() {
        hvCounter = CarStatus.hvVolt / 10;
        if (hvCounter < 0)
            hvVal = 0;
        else
            hvVal = Math.floor((hvCounter - 340) / 10);
    }

    Repeater {
        model: hvVal

        Image {
            id: hv

            source: hvnames[index]
            opacity: 1
        }

    }

    Image {
        id: hv

        source: "qrc:///qml/img/HV.png"
        opacity: 1
    }

    Image {
        id: hv1

        objectName: "hv1"
        source: "qrc:///qml/img/hv1.png"
        opacity: 1
    }

    Image {
        id: hv2

        objectName: "hv2"
        source: "qrc:///qml/img/hv2.png"
        opacity: 1
    }

}
