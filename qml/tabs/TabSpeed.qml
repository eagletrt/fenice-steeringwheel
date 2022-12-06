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
                            value: Car.steering.sc_values[Car.steering.slip_control_index] * 10
                            unit: "%"
                            label: "SLIP CONTROL"
                        }

                        ValueWithUnitAndLabel {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            valid: true
                            value: Car.steering.tv_values[Car.steering.torque_vectoring_index] * 10
                            unit: "%"
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

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    spacing: 80

                    CarStatus {
                    }

                    ValueWithUnitAndLabel {
                        valueFont: Style.mono.verybig
                        unitFont: Style.mono.h2
                        labelFont: Style.sans.h3
                        valid: true // Car.das.valid
                        value: Car.das.speed * 3.6
                        unit: "Km/h"
                        label: "SPEED"
                        high: 100
                    }

                }

                MapBar {
                    Layout.minimumHeight: 80
                    Layout.fillWidth: true
                    map: Car.steering.power_map_index
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
