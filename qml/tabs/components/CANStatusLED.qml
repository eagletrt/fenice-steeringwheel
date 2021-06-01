import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property var text

    // color: "#000000"
    color: "transparent"
    state: "CAN_DEFAULT"
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

            property color gradColor: "gray"

            width: 218
            height: 65
            radius: 50

            Text {
                id: ledText

                text: root.text
                anchors.centerIn: parent
                font: Style.sans.p
                color: "lightgray"
            }

            gradient: Gradient {
                GradientStop {
                    position: 0.8
                    color: "transparent"
                }

                GradientStop {
                    position: 0.9
                    color: led.gradColor
                }

            }

        }

    }

}
