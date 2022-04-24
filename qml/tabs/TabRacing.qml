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

    RowLayout {
        anchors.fill: parent

        ValueColumn {
            Layout.fillHeight: true
            Layout.minimumWidth: racing.columnWidth
            label: "[V] Battery"
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

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: Style.background

            ColumnLayout {
                anchors.fill: parent

                Item {
                    Layout.minimumHeight: 100
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueWithUnitAndLabel {
                                value: Car.inverters.left_temperature
                                unit: "°C"
                                label: "INVERTER L"
                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueWithUnitAndLabel {
                                value: Car.steering.map
                                unit: "%"
                                label: "MAX POWER"
                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueWithUnitAndLabel {
                                value: Car.inverters.right_temperature
                                unit: "°C"
                                label: "INVERTER R"
                            }

                        }

                    }

                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    ValueWithUnit {
                        unit: "km\nh"
                        value: Car.das.speed
                        valueFont: Style.mono.verybig
                        unitFont: Style.mono.h3
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
            label: "[kW] Battery"
            value: Car.hv.power
            maxDigits: 2
            max: 85
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
