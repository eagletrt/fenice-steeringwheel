import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    // color: "#000000"
    color: "transparent"

    state: "CAN_DEFAULT"

    property var text

    states: [
        State {
            name: "OK"
            PropertyChanges {
                target: led
                gradColor: "green"
            }
            PropertyChanges {
                target: ledText
                color: "lightgray"
            }
        },
        State {
            name: "NO"
            PropertyChanges {
                target: led
                gradColor: "red"
            }
            PropertyChanges {
                target: ledText
                color: "lightgray"
            }
        },
        State {
            name: "DEFAULT"
            PropertyChanges {
                target: led
                gradColor: "gray"
            }
            PropertyChanges {
                target: ledText
                color: "lightgray"
            }
        }
    ]

    Row {
        id: row
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: led
            width: 218
            height: 65
            radius: 50
            property color gradColor: "gray"
            gradient: Gradient {
                GradientStop { position: 0.8; color: "transparent" }
                GradientStop { position: 0.9; color: led.gradColor }
            }
            Text {
                id: ledText
                text: root.text
                anchors.centerIn: parent
                font.family: labelFont.name;
                font.pointSize: 10
                color: "lightgray"
            }
        }
    }
}
