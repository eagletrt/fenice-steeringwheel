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

    spacing: 5

    ValueWithUnit {
        anchors.horizontalCenter: parent.horizontalCenter

        value: root.value
        unit: root.unit
        valueFont: root.valueFont
        unitFont: root.unitFont
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter

        text: root.label
        color: Style.text
        font: root.labelFont
    }
}
