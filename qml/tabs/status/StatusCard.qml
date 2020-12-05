import Const 1.0
import QtQuick 2.0

Rectangle {
    id: root

    property string name

    state: "CAN_DEFAULT"
    anchors.fill: parent
    radius: 10
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

    Text {
        function chooseColor() {
            let R = parent.color.r;
            let G = parent.color.g;
            let B = parent.color.b;
            let l = Math.sqrt(0.299 * R * R + 0.587 * G * G + 0.114 * B * B);
            return l > 0.5 ? Style.background : Style.text;
        }

        anchors.centerIn: parent
        text: root.name
        color: chooseColor()
        font: Style.sans.p
    }

}
