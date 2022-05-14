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

                    ValueWithUnit {
                        Layout.alignment: Qt.AlignCenter
                        Layout.columnSpan: 2

                        value: 100
                        unit: "km/h"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.inverters.left_temperature
                        unit: "°C"
                        label: "INVERTER L"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.inverters.right_temperature
                        unit: "°C"
                        label: "INVERTER R"
                    }

                    ValueWithUnit {
                        Layout.alignment: Qt.AlignCenter
                        Layout.columnSpan: 2

                        value: 100
                        unit: "km/h"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.inverters.left_temperature
                        unit: "°C"
                        label: "MOTOR L"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.inverters.right_temperature
                        unit: "°C"
                        label: "MOTOR RIGHT"
                    }

                    Rectangle {
                        Layout.preferredWidth: parent.width / 2
                        Layout.fillHeight: true
                        Layout.columnSpan: 2
                        Layout.rowSpan: 2

                        color: Style.transparent
                        border.color: Style.surface
                        border.width: 1

                        GridLayout {
                            anchors.fill: parent
                            columns: 2
                            rows: 2
                            columnSpacing: 0
                            rowSpacing: 0

                            ValueWithUnitAndLabel {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                value: Car.inverters.left_temperature
                                unit: "°C"
                                label: "TYRE FL"
                            }

                            ValueWithUnitAndLabel {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                value: Car.inverters.right_temperature
                                unit: "°C"
                                label: "TYRE FR"
                            }

                            ValueWithUnitAndLabel {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                value: Car.inverters.left_temperature
                                unit: "°C"
                                label: "TYRE RL"
                            }

                            ValueWithUnitAndLabel {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                value: Car.inverters.right_temperature
                                unit: "°C"
                                label: "TYRE RR"
                            }
                        }
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.inverters.left_temperature
                        unit: "°C"
                        label: "BMS HV"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.inverters.right_temperature
                        unit: "°C"
                        label: "BMS LV"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.steering.map
                        unit: "%"
                        label: "OTHER"
                    }

                    ValueWithUnitAndLabel {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        value: Car.steering.map
                        unit: "%"
                        label: "OTHER"
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
