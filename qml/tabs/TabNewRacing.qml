import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.15
import "components"

Rectangle {
    //    Gauge {
    //        minimumValue: 0
    //        value: 50
    //        maximumValue: 100
    //        anchors.left: parent.left
    //        anchors.top: parent.top
    //        anchors.bottom: parent.bottom
    //        tickmarkAlignment: Qt.AlignRight
    //        font: Style.mono.p
    //        style: GaugeStyle {
    //            valueBar: Rectangle {
    //                color: Style.blue
    //                implicitWidth: 64
    //            }
    //        }
    //    }
    //    Gauge {
    //        minimumValue: 0
    //        value: 50
    //        maximumValue: 100
    //        anchors.right: parent.right
    //        anchors.top: parent.top
    //        anchors.bottom: parent.bottom
    //        tickmarkAlignment: Qt.AlignLeft
    //        font: Style.mono.p
    //        style: GaugeStyle {
    //            valueBar: Rectangle {
    //                color: Style.green
    //                implicitWidth: 64
    //            }
    //        }
    //    }

    id: racing

    property int columnWidth: 100

    color: Style.background

    CircularGauge {
        id: gauge

        property bool accelerating: false

        value: accelerating ? maximumValue : 0
        anchors.centerIn: parent
        width: 380
        height: 380
        Keys.onSpacePressed: accelerating = true
        Keys.onReleased: {
            if (event.key === Qt.Key_Space) {
                accelerating = false;
                event.accepted = true;
            }
        }
        Component.onCompleted: forceActiveFocus()

        Behavior on value {
            NumberAnimation {
                duration: 1000
            }

        }

        style: CircularGaugeStyle {
            minimumValueAngle: -180
            maximumValueAngle: 45

            needle: Rectangle {
                y: -outerRadius * 0.3
                implicitWidth: outerRadius * 0.025
                implicitHeight: outerRadius * 0.7
                antialiasing: true
            }

            foreground: Item {
                anchors.fill: parent

                Image {
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:///qml/img/eagle.png"
                    x: outerRadius * 0.75
                    y: outerRadius * 0.75
                    width: outerRadius * 0.5
                    height: outerRadius * 0.5
                }

                Item {
                    x: outerRadius
                    y: outerRadius * 0.5
                    width: outerRadius
                    height: outerRadius

                    ColumnLayout {
                        anchors.fill: parent
                        ColumnLayout {
                            Layout.alignment: Qt.AlignRight
                            Layout.preferredWidth: 120

                            Text {
                                Layout.alignment: Qt.AlignHCenter
                                text: gauge.value.toFixed(0)
                                font.family: Style.mono.family
                                font.pointSize: Style.sizes.big
                                color: Style.text
                            }

                            Text {
                                Layout.alignment: Qt.AlignHCenter
                                text: "km/h"
                                font.family: Style.sans.family
                                font.pointSize: Style.sizes.small
                                color: Style.text
                            }

                        }

                    }

                }

            }

            tickmarkLabel: Text {
                text: styleData.value
                font: Style.mono.p
                color: Style.text
            }

        }

    }

}
