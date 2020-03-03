import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "transparent"
    FontLoader {id:blackops; source: "../lib/blops.ttf"}
    property var text
    property var ledColor

    states: [
        State {
            name: "on"
            PropertyChanges {
                target: statusLed
                color: root.ledColor
            }
        },
        State {
            name: 'off'
            PropertyChanges {
                target: statusLed
                color: "#333333"
            }
        },
        State {
            name: 'disabled'
            PropertyChanges {
                target: statusLed
                color: "#333333"
            }
            PropertyChanges {
                target: statusText
                color: "#333333"
            }
        }
    ]

    GridLayout {
        anchors.fill: parent
        columns: 4

        Rectangle {
            color: "transparent"
            Layout.preferredWidth: root.width / 4
            Layout.fillHeight: true

            Rectangle {
                id: statusLed
                anchors.centerIn: parent
                height: 20
                width: 20
                radius: 20
            }
        }

        Rectangle {
            Layout.preferredWidth: root.width / 2
            Layout.fillHeight: true
            color: "transparent"

            Text {
                id: statusText
                anchors.verticalCenter: parent.verticalCenter

                text: root.text
                font.pointSize: 18
                font.family: blackops.name;
                color: "lightgray"
            }
        }

    }
}
