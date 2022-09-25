import Const 1.0
import QtQuick 2.0

Rectangle {
    id: root

    property string title
    property string subtitle

    state: "DEFAULT"
    states: [
        State {
            name: "NORMAL"

            PropertyChanges {
                target: root
                color: Style.status.ok
            }

        },
        State {
            name: "ERROR"

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
            text: root.title
            color: Style.textInverted
            font: Style.sans.h3
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.subtitle
            color: Style.darker
            font: Style.mono.small
        }

    }

}
