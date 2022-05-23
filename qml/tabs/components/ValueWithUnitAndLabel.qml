import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Column {
    id: root

    property int value
    property string unit
    property string label
    property font valueFont: Style.mono.h1
    property font unitFont: Style.mono.p
    property font labelFont: Style.sans.small
    property real high: 100
    property real medhigh: 60
    property real medlow: 0
    property real low: -10

    spacing: 5

    ValueWithUnit {
        id: main
        anchors.horizontalCenter: parent.horizontalCenter

        high: root.high
        medhigh: root.medhigh
        medlow: root.medlow
        low: root.low

        value: root.value
        unit: root.unit
        valueFont: root.valueFont
        unitFont: root.unitFont
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter

        text: root.label
        color: main.color
        font: root.labelFont
    }
}
