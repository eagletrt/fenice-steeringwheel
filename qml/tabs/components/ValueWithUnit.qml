import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int value
    property string unit
    property font valueFont: Style.mono.h1
    property font unitFont: Style.sans.p
    property color color: Style.text
    property real high: +Infinity
    property real medhigh: +Infinity
    property real medlow: -Infinity
    property real low: -Infinity

    width: main.width
    height: main.height

    states: [
        State {
            name: "HIGH"
            when: value >= high

            PropertyChanges {
                target: root
                color: Style.red
            }
        },
        State {
            name: "MEDHIGH"
            when: value >= medhigh

            PropertyChanges {
                target: root
                color: Style.orange
            }
        },
        State {
            name: "LOW"
            when: value <= low

            PropertyChanges {
                target: root
                color: Style.blue
            }
        },
        State {
            name: "MEDLOW"
            when: value <= medlow

            PropertyChanges {
                target: root
                color: Style.aqua
            }
        },
        State {
            name: "NORMAL"
            when: true

            PropertyChanges {
                target: root
                color: Style.text
            }
        }
    ]

    Text {
        id: main
        text: root.value
        font: root.valueFont
        color: root.color

        horizontalAlignment: Text.right
    }

    Text {
        id: other
        anchors.left: main.right
        anchors.leftMargin: 4
        anchors.verticalCenter: main.verticalCenter

        text: root.unit
        font: root.unitFont
        color: root.color
    }
}
