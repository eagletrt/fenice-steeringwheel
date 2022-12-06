import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Rectangle {
    id: speed

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
                Layout.minimumWidth: speed.columnWidth
                label: "[V] BMS"
                valid: Car.hv.valid
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
                Layout.topMargin: 95
                Layout.minimumWidth: 15
                value: Car.hv.pack_voltage
                valid: Car.hv.valid
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
                            valid: true
                            value: Car.steering.sc_values[Car.steering.slip_control_index]
                            unit: "val"
                            label: "SLIP CONTROL"
                        }

                        ValueWithUnitAndLabel {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            valid: true
                            value: Car.steering.tv_values[Car.steering.torque_vectoring_index]
                            unit: "val"
                            label: "TORQUE VECTORING"
                        }

                        ValueWithUnitAndLabel {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            valid: true
                            value: Car.steering.pm_values[Car.steering.power_map_index] * 10
                            unit: "%"
                            label: "MAX POWER"
                        }

                    }

                }

                Item {
                    Layout.fillHeight: true
                    Layout.leftMargin: 60

                    Speedometer {
                        property bool accelerating: false

                        speed: accelerating ? 180 : 0
                        Keys.onSpacePressed: accelerating = true
                        Keys.onReleased: {
                            if (event.key === Qt.Key_Space) {
                                accelerating = false;
                                event.accepted = true;
                            }
                        }
                        Component.onCompleted: forceActiveFocus()
                        objectName: "speedometer"
                        width: speedometerSize
                        height: speedometerSize

                        Behavior on speed {
                            NumberAnimation {
                                duration: 1000
                            }

                        }

                    }

                }

                MapBar {
                    Layout.minimumHeight: 80
                    Layout.fillWidth: true
                    map: Car.steering.power_map * 10
                }

            }

        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            Bar {
                Layout.fillHeight: true
                Layout.topMargin: 95
                Layout.minimumWidth: 15
                valid: Car.hv.valid
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
                Layout.minimumWidth: speed.columnWidth
                label: "[V] BMS"
                valid: Car.hv.valid
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
