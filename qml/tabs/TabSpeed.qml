import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Rectangle {
    id: racing

    property int columnWidth: 80

    color: Style.background

    RowLayout {
        anchors.fill: parent
        spacing: 5

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0
            ValueColumn {
                Layout.fillHeight: true
                Layout.minimumWidth: racing.columnWidth
                label: "[V] BMS"
                value: Car.hv.pack_voltage
                max: 460
                maxDigits: 3
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

            Bar {
                Layout.fillHeight: true
                Layout.topMargin: 85
                Layout.minimumWidth: 15

                value: Car.hv.pack_voltage
                max: 460
                maxDigits: 3
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
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                Item {
                    Layout.minimumHeight: 100
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent

                        ValueWithUnitAndLabel {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            value: Car.inverters.left_temperature
                            unit: "°C"
                            label: "INVERTER L"
                        }

                        ValueWithUnitAndLabel {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            value: Car.steering.map
                            unit: "%"
                            label: "MAX POWER"
                        }

                        ValueWithUnitAndLabel {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            value: Car.inverters.right_temperature
                            unit: "°C"
                            label: "INVERTER R"
                        }
                    }
                }

                Item {
                    Layout.fillHeight: true
                    Layout.leftMargin: 60

                    Speedometer {
                        speed: accelerating ? 180 : 0

                        property bool accelerating: false

                        Keys.onSpacePressed: accelerating = true
                        Keys.onReleased: {
                            if (event.key === Qt.Key_Space) {
                                accelerating = false;
                                event.accepted = true;
                            }
                        }

                        Component.onCompleted: forceActiveFocus()

                        Behavior on speed  {
                            NumberAnimation {
                                duration: 1000
                            }
                        }

                        objectName: "speedometer"
                        width: speedometerSize
                        height: speedometerSize
                    }
                }

                MapBar {
                    Layout.minimumHeight: 80
                    Layout.fillWidth: true

                    map: Car.steering.map
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            Bar {
                Layout.fillHeight: true
                Layout.topMargin: 85
                Layout.minimumWidth: 15

                value: Car.hv.pack_voltage
                max: 460
                maxDigits: 3
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
            ValueColumn {
                Layout.fillHeight: true
                Layout.minimumWidth: racing.columnWidth
                label: "[V] BMS"
                value: Car.hv.pack_voltage
                max: 460
                maxDigits: 3
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
        }
    }
}
