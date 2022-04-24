import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int value
    property string unit
    property string label
    property font valueFont: Style.mono.h1
    property font unitFont: Style.mono.p
    property font labelFont: Style.sans.small

    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ValueWithUnit {
                value: root.value
                unit: root.unit
                valueFont: root.valueFont
                unitFont: root.unitFont
            }

        }

        Item {
            Layout.fillWidth: true
            Layout.minimumHeight: childrenRect.height

            Text {
                anchors.centerIn: parent
                text: root.label
                color: Style.text
                font: root.labelFont
            }

        }

    }

}
