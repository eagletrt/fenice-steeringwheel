import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property real value
    property string unit
    property bool valid: true
    property int decimals: 0
    property font valueFont: Style.mono.h1
    property font unitFont: Style.sans.xsmall
    property color color: Style.text
    property real high: +Infinity
    property real low: -Infinity
    property real medhigh: root.high * 0.8
    property real medlow: root.low * 1.1

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

        text: root.value.toFixed(root.decimals).substring(0, 3)
        font: root.valueFont
        color: root.color
        horizontalAlignment: Text.right
    }

    Text {
        id: other

        anchors.left: main.right
        anchors.leftMargin: 2
        anchors.verticalCenter: main.verticalCenter
        text: root.unit
        font: root.unitFont
        color: root.color
    }

}
