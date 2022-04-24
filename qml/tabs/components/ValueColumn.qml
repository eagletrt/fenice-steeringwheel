import Const 1.0
import QtGraphicalEffects 1.12
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root

    property double value: 0
    property double max: 1
    property int maxDigits: 3
    property int barCount: 10
    property string label
    property Gradient columnGradient

    color: Style.background

    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.minimumHeight: 80
            Layout.fillWidth: true

            ValueWithUnitAndLabel {
                value: root.value.toFixed().padStart(root.maxDigits, " ")
                label: root.label
                labelFont: Style.sans.xsmall
            }

        }

        ProgressBar {
            id: valueBar

            value: root.value
            to: root.max
            Layout.fillWidth: true
            Layout.fillHeight: true
            rotation: 180

            background: Rectangle {
                color: Style.surface
            }

            contentItem: Item {
                Rectangle {
                    id: source

                    anchors.fill: parent
                    visible: false
                    gradient: columnGradient
                }

                Rectangle {
                    id: mask

                    anchors.fill: parent
                    color: "transparent"

                    Rectangle {
                        width: parent.width
                        height: parent.height * valueBar.visualPosition
                        color: "black"
                    }

                }

                OpacityMask {
                    anchors.fill: parent
                    source: source
                    maskSource: mask
                }

                Column {
                    Repeater {
                        model: root.barCount

                        Rectangle {
                            width: valueBar.width
                            height: valueBar.height / root.barCount
                            color: "transparent"
                            border.width: 1
                        }

                    }

                }

            }

        }

    }

}
