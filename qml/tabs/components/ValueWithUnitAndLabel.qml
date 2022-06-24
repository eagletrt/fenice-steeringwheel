import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Column {
    id: root

    property real value
    property string unit
    property string label
    property bool valid: true
    property int decimals: 0
    property font valueFont: Style.mono.h1
    property font unitFont: Style.mono.p
    property font labelFont: Style.sans.small
    property real high: +Infinity
    property real low: -Infinity
    property real medhigh: root.high * 0.8
    property real medlow: root.low * 1.1

    spacing: 5

    ValueWithUnit {
        id: main

        anchors.horizontalCenter: parent.horizontalCenter
        high: root.high
        medhigh: root.medhigh
        medlow: root.medlow
        low: root.low
        valid: root.valid
        value: root.value
        unit: root.unit
        valueFont: root.valueFont
        unitFont: root.unitFont
        decimals: root.decimals
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: root.label
        color: main.color
        font: root.labelFont
    }
}
