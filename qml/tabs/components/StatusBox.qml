import Const 1.0
import QtQuick 2.0

Rectangle {
    id: root

    property string name
    property string version: "v1.0.0"

    state: "DEFAULT"
    anchors.fill: parent
    states: [
        State {
            name: "OK"

            PropertyChanges {
                target: root
                color: Style.status.ok
            }
        },
        State {
            name: "NO"

            PropertyChanges {
                target: root
                color: Style.status.error
            }
        },
        State {
            name: "OUTDATED"

            PropertyChanges {
                target: root
                color: Style.status.warn
            }
        },
        State {
            name: "DEFAULT"

            PropertyChanges {
                target: root
                color: Style.status.def
            }
        }
    ]

    Column {
        anchors.centerIn: parent

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.name
            color: Style.textInverted
            font: Style.sans.h3
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.version
            color: Style.darker
            font: Style.mono.small
        }
    }
}
