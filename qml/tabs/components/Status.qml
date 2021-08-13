import QtQuick 2.7

Rectangle {
    id: root

    property string text
    property int fontsize

    height: parent.height
    anchors.verticalCenter: parent.verticalCenter
    states: [
        State {
            name: "run"

            PropertyChanges {
                target: root
                color: "green"
                text: "RUN"
            }

        },
        State {
            name: "idle"

            PropertyChanges {
                target: root
                color: "orange"
                text: "IDLE"
            }

        },
        State {
            name: "stop"

            PropertyChanges {
                target: root
                color: "red"
                text: "STOP"
            }

        },
        State {
            name: "off"

            PropertyChanges {
                target: root
                color: "grey"
                text: "RADIO"
            }

        },
        State {
            name: "on"

            PropertyChanges {
                target: root
                color: "teal"
                text: "RADIO"
            }

        }
    ]

    Text {
        id: statusText

        anchors.centerIn: parent
        font.pointSize: root.fontsize
        text: root.text
        padding: 5
        color: "lightgray"
    }

}
