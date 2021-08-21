import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Rectangle {
    id: racing

    property int columnWidth: 100

    function connect() {
        window.onMapChanged.connect(onMapChanged);
    }

    function disconnect() {
        window.onMapChanged.disconnect(onMapChanged);
    }

    function onMapChanged(map) {
        mapBar.map = Math.min(map, mapBar.maps.length - 1);
    }

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
            label: "[V] Porco"
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
                                label: "DCDC"
                                value: Car.lv.dcdcTemperature
                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "°C"
                                label: "Battery"
                                value: Car.lv.batteryTemperature
                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "°C"
                                label: "HV"
                                value: Car.hv.averageTemperature
                            }

                        }

                    }

                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            BigValue {
                                unit: "wh\nkm"
                                value: 100
                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            BigValue {
                                unit: "km\nh"
                            }

                        }

                    }

                }

                Item {
                    Layout.minimumHeight: 80
                    Layout.fillWidth: true

                    MapBar {
                        id: mapBar
                    }

                }

            }

        }

        ValueColumn {
            Layout.fillHeight: true
            Layout.minimumWidth: racing.columnWidth
            label: "[kw] Porco"
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
