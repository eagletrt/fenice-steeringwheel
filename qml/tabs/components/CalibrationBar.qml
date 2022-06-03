import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
    id: root

    property string name: "DEMO"
    property string color: "red"
    property double value: 0
    property double zero: 0
    property color background: Style.surface

    Rectangle {
        anchors.fill: parent
        color: root.background

        Control {
            anchors.fill: parent
            padding: 20

            contentItem: RowLayout {
                Item {
                    Layout.preferredWidth: nameWidth
                    Layout.fillHeight: true

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        text: root.name
                        color: Style.textInverted
                        font: Style.sans.h3
                    }

                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ProgressBar {
                        id: sensorValue

                        anchors.fill: parent
                        value: root.value

                        background: Rectangle {
                            color: Style.dark
                        }

                        contentItem: Item {
                            rotation: sensorValue.visualPosition > root.zero ? 0 : 180

                            Rectangle {
                                x: sensorValue.width * root.zero
                                width: sensorValue.width * Math.abs(root.zero - sensorValue.visualPosition)
                                height: parent.height
                                color: root.color
                            }

                            Row {
                                Repeater {
                                    model: 10

                                    Rectangle {
                                        width: sensorValue.width / 10
                                        height: sensorValue.height
                                        color: "transparent"
                                        border.width: 1
                                    }

                                }

                            }

                        }

                    }

                }

                Item {
                    Layout.preferredWidth: valueWidth
                    Layout.fillHeight: true

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        text: ((sensorValue.visualPosition - root.zero) * 100).toFixed(0) + "%"
                        color: Style.textInverted
                        font: Style.mono.h3
                    }

                }

            }

        }

    }

}
