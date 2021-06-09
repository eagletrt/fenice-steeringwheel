import Const 1.0
import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: calibration

    property var sensors: [{
        "name": "APPS",
        "color": Style.green,
        "zero": 0
    }, {
        "name": "BSE",
        "color": Style.red,
        "zero": 0
    }, {
        "name": "STEER",
        "color": Style.yellow,
        "zero": 0.5
    }]
    property var values: [0.2, 0.5, 0.2]
    property int nameWidth: 130
    property int valueWidth: 100

    padding: 20

    contentItem: GridLayout {
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        Repeater {
            model: sensors

            delegate: Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.columnSpan: 2
                color: Style.surface

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
                                text: modelData.name
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

                                SequentialAnimation on value {
                                    loops: Animation.Infinite

                                    NumberAnimation {
                                        from: 0
                                        to: 1
                                        duration: 2500
                                    }

                                    NumberAnimation {
                                        from: 1
                                        to: 0
                                        duration: 2500
                                    }

                                }

                                background: Rectangle {
                                    color: Style.dark
                                }

                                contentItem: Item {
                                    rotation: sensorValue.visualPosition > modelData.zero ? 0 : 180

                                    Rectangle {
                                        x: sensorValue.width * modelData.zero
                                        width: sensorValue.width * Math.abs(modelData.zero - sensorValue.visualPosition)
                                        height: parent.height
                                        color: modelData.color
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
                                text: ((sensorValue.visualPosition - modelData.zero) * 100).toFixed(0) + "%"
                                color: Style.textInverted
                                font: Style.mono.h3
                            }

                        }

                    }

                }

            }

        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Style.blue

            Text {
                anchors.centerIn: parent
                text: "Set Min"
                color: Style.textInverted
                font: Style.sans.h3
            }

        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Style.orange

            Text {
                anchors.centerIn: parent
                text: "Set Max"
                color: Style.textInverted
                font: Style.sans.h3
            }

        }

    }

}
