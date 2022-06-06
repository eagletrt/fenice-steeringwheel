import Const 1.0
import QtGraphicalEffects 1.12
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property double value: 0
    property string label
    property double max: 1
    property int maxDigits: 3
    property int barCount: 10
    property int rotation: 180
    property Gradient columnGradient

    ColumnLayout {
        anchors.fill: parent

        ValueWithUnitAndLabel {
            Layout.minimumHeight: 90
            Layout.fillWidth: true
            value: root.value.toFixed().padStart(root.maxDigits, " ")
            label: root.label
            labelFont: Style.sans.xsmall
        }

        Bar {
            Layout.fillWidth: true
            Layout.fillHeight: true
            value: root.value
            max: root.max
            maxDigits: root.maxDigits
            barCount: root.barCount
            columnGradient: root.columnGradient
            rotation: root.rotation
        }
    }
}
