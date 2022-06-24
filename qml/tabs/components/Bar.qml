import Const 1.0
import QtGraphicalEffects 1.12
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ProgressBar {
    id: root

    property bool valid: true
    property double max: 1
    property int maxDigits: 3
    property int barCount: 10
    property Gradient columnGradient

    value: valid ? value : "N/A"
    to: max
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
                height: parent.height * root.visualPosition
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
                    width: root.width
                    height: root.height / root.barCount
                    color: "transparent"
                    border.width: 1
                }
            }
        }
    }
}
