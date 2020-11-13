import QtQuick 2.0

Item {
    property var lvVolt: CarStatus.lvVolt
    property int lvVal: lvVolt
    property int lvCounter: lvVal
    property variant lvnames: ["qrc:///qml/img/lv3.png", "qrc:///qml/img/lv4.png", "qrc:///qml/img/lv5.png", "qrc:///qml/img/lv6.png", "qrc:///qml/img/lv7.png", "qrc:///qml/img/lv8.png", "qrc:///qml/img/lv9.png", "qrc:///qml/img/lv10.png", "qrc:///qml/img/lv11.png", "qrc:///qml/img/lv12.png", "qrc:///qml/img/lv13.png", "qrc:///qml/img/lv14.png", "qrc:///qml/img/lv15.png"] //"qrc:///qml/img/lv16.png"

    onLvVoltChanged: function() {
        lvCounter = CarStatus.lvVolt - 80;
        if (lvCounter < 0)
            lvVal = 0;
        else
            lvVal = Math.floor(lvCounter / 10);
    }

    Repeater {
        model: lvVal

        Image {
            id: lv

            source: lvnames[index]
            opacity: 1
        }

    }

    Image {
        id: lv

        source: "qrc:///qml/img/LV.png"
        opacity: 1
    }

    Image {
        id: lv1

        objectName: "lv1"
        source: "qrc:///qml/img/lv1.png"
        opacity: 1
    }

    Image {
        id: lv2

        objectName: "lv2"
        source: "qrc:///qml/img/lv2.png"
        opacity: 1
    }

}
