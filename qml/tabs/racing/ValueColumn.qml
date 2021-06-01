import Const 1.0
import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: valueColumn

    property double value: 0
    property string label
    property int barCount: 10
    property int direction: Qt.LeftToRight
    property Gradient columnGradient

    color: Style.background

    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.minimumHeight: childrenRect.height
            Layout.fillWidth: true

            Column {
                anchors.centerIn: parent
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font: Style.mono.h3
                    color: Style.text
                    text: (valueColumn.value * 400).toFixed().padStart(3, " ")
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: valueColumn.label
                    color: Style.text
                    font: Style.sans.small
                }

            }

        }

        ProgressBar {
            id: valueBar

            value: valueColumn.value
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
                        model: valueColumn.barCount

                        Rectangle {
                            width: valueBar.width
                            height: valueBar.height / valueColumn.barCount
                            color: "transparent"
                            border.width: 1
                        }

                    }

                }

            }

        }

    }

}
