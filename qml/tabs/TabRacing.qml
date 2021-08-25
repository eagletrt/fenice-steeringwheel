import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Rectangle {
    id: racing

    property int columnWidth: 100

    color: Style.background

    Timer {
        property real start: Date.now()

        interval: 10
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: function update() {
            let d = new Date(Date.now() - start);
            time.text = String(d.getUTCMinutes()).padStart(2, "0") + ":" + String(d.getUTCSeconds()).padStart(2, "0") + "." + String((Math.min(99, d.getUTCMilliseconds() / 10)).toFixed()).padStart(2, "0");
        }
    }

    RowLayout {
        anchors.fill: parent

        ValueColumn {
            Layout.fillHeight: true
            Layout.minimumWidth: racing.columnWidth
            label: "[V] Battery"
            barCount: 8

            columnGradient: Gradient {
                GradientStop {
                    position: 1
                    color: Style.red
                }

                GradientStop {
                    position: 0
                    color: Style.orange
                }

            }

        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: Style.background

            ColumnLayout {
                anchors.fill: parent

                Item {
                    Layout.minimumHeight: childrenRect.height
                    Layout.fillWidth: true

                    Text {
                        id: time

                        anchors.centerIn: parent
                        color: Style.text
                        font: Style.mono.big
                    }

                }

                Item {
                    Layout.minimumHeight: 100
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "°C"
                                label: "INVERTER L"
                                value: Car.lv.dcdcTemperature
                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "%"
                                label: "MAX POWER"
                                value: Car.steering.map * 20
                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "°C"
                                label: "INVERTER R"
                                value: Car.hv.averageTemperature
                            }

                        }

                    }

                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    BigValue {
                        unit: "wh\nkm"
                        value: 100
                    }

                }

                Item {
                    Layout.minimumHeight: 80
                    Layout.fillWidth: true

                    MapBar {
                        map: Car.steering.map
                    }

                }

            }

        }

        ValueColumn {
            Layout.fillHeight: true
            Layout.minimumWidth: racing.columnWidth
            label: "[kw] Battery"
            barCount: 8

            columnGradient: Gradient {
                GradientStop {
                    position: 1
                    color: Style.blue
                }

                GradientStop {
                    position: 0
                    color: Style.aqua
                }

            }

        }

    }

}
