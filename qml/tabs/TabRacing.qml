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
                valid: Car.hv.valid
                value: Car.hv.bus_voltage
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

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                GridLayout {
                    anchors.fill: parent
                    columns: 4
                    rows: 3

                    Text {
                        id: car_status

                        Layout.alignment: Qt.AlignCenter
                        Layout.columnSpan: 2
                        font: Style.sans.h1
                        color: Style.text
                        states: [
                            State {
                                name: "IDLE"
                                when: Car.das.car_status === 0

                                PropertyChanges {
                                    target: car_status
                                    text: "IDLE"
                                }

                            },
                            State {
                                name: "PRE SETUP"
                                when: Car.das.car_status === 1

                                PropertyChanges {
                                    target: car_status
                                    text: "PRE SETUP"
                                }

                            },
                            State {
                                name: "TS ON"
                                when: Car.das.car_status === 2

                                PropertyChanges {
                                    target: car_status
                                    text: "TS ON"
                                }

                            },
                            State {
                                name: "POST SETUP"
                                when: Car.das.car_status === 3

                                PropertyChanges {
                                    target: car_status
                                    text: "POST SETUP"
                                }

                            },
                            State {
                                name: "DRIVE"
                                when: Car.das.car_status === 4

                                PropertyChanges {
                                    target: car_status
                                    text: "DRIVE"
                                }

                            },
                            State {
                                name: "TEARDOWN"
                                when: Car.das.car_status === 5

                                PropertyChanges {
                                    target: car_status
                                    text: "TEARDOWN"
                                }

                            },
                            State {
                                name: "???"
                                when: true

                                PropertyChanges {
                                    target: car_status
                                    text: "???"
                                }

                            }
                        ]
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.hv.valid
                        value: Car.hv.max_temperature
                        unit: "°C"
                        label: "HV BATT"
                        high: 50
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.lv.valid
                        value: Car.lv.battery_temperature
                        unit: "°C"
                        label: "LV BATT"
                    }

                    Text {
                        Layout.alignment: Qt.AlignCenter
                        Layout.columnSpan: 2
                        font: Style.sans.h2
                        color: Style.text
                        text: "TUPIDO"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.hv.valid
                        value: Car.hv.current
                        unit: "A"
                        label: "HV CURR"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.lv.valid
                        value: Car.lv.dcdc_temperature
                        unit: "°C"
                        label: "LV DCDC"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.das.valid
                        value: Car.inverters.right_temperature
                        unit: "°C"
                        label: "INVERTER L"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.das.valid
                        value: Car.inverters.left_temperature
                        unit: "°C"
                        label: "INVERTER R"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.hv.valid
                        value: Car.hv.min_cell_voltage
                        unit: "V"
                        label: "HV MIN"
                        decimals: 1
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.lv.valid
                        value: Car.lv.voltage_min
                        decimals: 1
                        unit: "V"
                        label: "LV MIN"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: 0
                        unit: "°C"
                        label: "OTHER"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: true
                        value: Car.steering.temperature
                        unit: "°C"
                        label: "STEER"
                        high: 80
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.hv.valid
                        value: 1000 * (Car.hv.max_cell_voltage - Car.hv.min_cell_voltage)
                        unit: "mV"
                        label: "HV DIFF"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        valid: Car.lv.valid
                        value: 1000 * (Car.lv.voltage_max - Car.lv.voltage_min)
                        unit: "mV"
                        label: "LV DIFF"
                    }

                }

            }

            MapBar {
                Layout.minimumHeight: 80
                Layout.fillWidth: true
                map: Car.steering.map
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
                valid: Car.lv.valid
                value: Car.lv.current
                max: 30
                maxDigits: 2
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

            ValueColumn {
                Layout.fillHeight: true
                Layout.minimumWidth: racing.columnWidth
                label: "[A] BMS LV"
                valid: Car.lv.valid
                value: Car.lv.current
                max: 30
                maxDigits: 3
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

}
