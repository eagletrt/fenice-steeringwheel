import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "#000000"

    state: "CAN_DEFAULT"

    FontLoader {id:blackops; source: "../lib/blops.ttf"}

    property var text

    states: [
        State {
            name: "OK"
            PropertyChanges {
                target: led
                color: "green"
            }
        },
        State {
            name: "NO"
            PropertyChanges {
                target: led
                color: "red"
            }
        },
        State {
            name: "DEFAULT"
            PropertyChanges {
                target: led
                color: "lightgray"
            }
        }
    ]

    Row {
        id: row
        anchors.fill: parent
        spacing: 0

        Rectangle {
            width: root.width * 3/6
            height: root.height
            color: "transparent"

            Text {
                anchors.centerIn: parent
                text: root.text
                font.family: blackops.name;
                font.pointSize: 5
                color: "lightgray"
            }
        }

        Rectangle {
            color: "transparent"
            width: root.width * 3/6
            height: root.height

            Rectangle {
                id: led
                anchors.centerIn: parent
                width: 30
                height: 30
                radius: 30
                color: "transparent"
            }
        }

    }
}
