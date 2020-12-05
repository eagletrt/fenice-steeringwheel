import Const 1.0
import QtQuick 2.7

Rectangle {
    property int hvTemp: CarStatus.hvTemp
    property int hvVolt: CarStatus.hvVolt
    property int lvTemp: CarStatus.lvTemp
    property int lvVolt: CarStatus.lvVolt
    property int velocity: CarStatus.velocity
    property int speed: CarStatus.speed
    property int km: CarStatus.km
    property int invSxTemp: CarStatus.invSxTemp
    property int invDxTemp: CarStatus.invDxTemp
    property variant throttlenames: ["qrc:///qml/img/t1.png", "qrc:///qml/img/t2.png", "qrc:///qml/img/t3.png", "qrc:///qml/img/t4.png", "qrc:///qml/img/t5.png", "qrc:///qml/img/t6.png", "qrc:///qml/img/t7.png", "qrc:///qml/img/t8.png", "qrc:///qml/img/t9.png", "qrc:///qml/img/t10.png"]
    property variant brakenames: ["qrc:///qml/img/b1.png", "qrc:///qml/img/b2.png", "qrc:///qml/img/b3.png", "qrc:///qml/img/b4.png", "qrc:///qml/img/b5.png", "qrc:///qml/img/b6.png", "qrc:///qml/img/b7.png", "qrc:///qml/img/b8.png", "qrc:///qml/img/b9.png", "qrc:///qml/img/b10.png"]
    property int brakeidx: 0
    property int throttleidx: 0

    color: "transparent"

    Text {
        id: textVelocity

        text: velocity + " KW"
        font: Style.mono.p
        y: 290
        x: 160
        width: 200
        horizontalAlignment: Text.AlignHCenter
        color: "lightgray"
    }

    Text {
        id: textKm

        text: km + " m"
        font: Style.mono.p
        y: 290
        x: 260
        width: 200
        horizontalAlignment: Text.AlignHCenter
        color: "lightgray"
    }

    Text {
        id: textInvSxTemp

        text: invSxTemp / 10 + "°C"
        font: Style.mono.p
        x: 10
        y: 160
        color: "lightgray"
    }

    Text {
        id: textInvDxTemp

        text: invDxTemp / 10 + "°C"
        horizontalAlignment: Text.AlignLeft
        font: Style.mono.p
        x: 610
        y: 160
        width: 70
        color: "lightgray"
    }

    Text {
        // property int hvTemp: CarStatus.hvTemp

        id: texthvTemp

        text: hvTemp / 10 + " °C"
        font: Style.mono.p
        x: 10
        y: 220
        color: "lightgray"
    }

    Text {
        // property int hvVolt: CarStatus.hvVolt / 10

        id: texthvVolt

        text: hvVolt / 10 + " V"
        font: Style.mono.p
        x: 10
        y: 260
        color: "lightgray"
    }

    Text {
        // property int lvTemp: CarStatus.lvTemp

        id: textlvTemp

        text: lvTemp / 5 + " °C"
        horizontalAlignment: Text.AlignLeft
        font: Style.mono.p
        x: 610
        y: 220
        width: 70
        color: "lightgray"
    }

    Text {
        // property int lvVolt: CarStatus.lvVolt

        id: textlvVolt

        text: lvVolt / 10 + " V"
        horizontalAlignment: Text.AlignLeft
        font: Style.mono.p
        x: 610
        y: 260
        width: 70
        color: "lightgray"
    }

    Text {
        id: carSpeed

        text: speed
        font: Style.mono.h1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -15
        color: "lightgray"
    }

    Text {
        text: "km/h"
        font: Style.sans.p
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 48
        color: "lightgray"
    }

    Item {
        property var throttleVal: CarStatus.throttleVal
        property int throttleValore: throttleVal

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -310
        anchors.horizontalCenterOffset: -430
        onThrottleValChanged: function() {
            throttleValore = CarStatus.throttleVal;
            throttleidx = throttleValore / 10;
        }

        Repeater {
            model: throttleidx

            Image {
                id: throttles

                source: throttlenames[index]
                opacity: 1
            }

        }

    }

    Item {
        // console.log(brakeidx)

        property var brakeVal: CarStatus.brakeVal
        property int brakeValore: brakeVal

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -295
        anchors.horizontalCenterOffset: -380
        onBrakeValChanged: function() {
            brakeValore = CarStatus.brakeVal;
            brakeidx = brakeValore / 10;
        }

        Repeater {
            model: brakeidx

            Image {
                id: breaks

                source: brakenames[index]
                opacity: 1
            }

        }

    }

    Item {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -295
        anchors.horizontalCenterOffset: -380

        Image {
            id: thr

            source: "qrc:///qml/img/thr.png"
            opacity: 1
        }

    }

    Item {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -295
        anchors.horizontalCenterOffset: -380

        Image {
            id: brk

            source: "qrc:///qml/img/brk.png"
            opacity: 1
        }

    }

}
