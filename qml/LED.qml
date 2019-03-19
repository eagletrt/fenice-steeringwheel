import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "transparent"

    state: "DEFAULT"

    states: [
        State {
            name: "OK"
            PropertyChanges {
                target: innerLED
                color: "green"
            }
        },
        State {
            name: "NO"
            PropertyChanges {
                target: innerLED
                color: "red"
            }
        },
        State {
            name: "DEFAULT"
            PropertyChanges {
                target: innerLED
                color: "grey"
            }
        }
    ]

    Rectangle {
        id: innerLED
        width: root.width
        height: root.width
        radius: root.height/4
    }
}
