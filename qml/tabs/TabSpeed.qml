import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Speedometer 1.0
import "components"

Rectangle {
    id: racing

    property int columnWidth: 100

    color: Style.background

    function connect() {
        window.buttonPressed.connect(onButtonPressed);
        window.buttonReleased.connect(onButtonReleased);
    }

    function disconnect() {
        window.buttonPressed.disconnect(onButtonPressed);
        window.buttonReleased.disconnect(onButtonReleased);
    }

    function onButtonPressed(button) {
        if (button === Input.increaseSpeed)
            Car.das.speed += 0.8;
        else if (button === Input.decreaseSpeed)
            Car.das.speed -= 0.8;
    }

    function onButtonReleased(button) {
    }

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
                        objectName: "speedometer"
                        width: speedometerSize
                        height: speedometerSize
                        speed: Car.das.speed
                    }
                }

                MapBar {
                    Layout.minimumHeight: 80
                    Layout.fillWidth: true

                    map: Car.steering.map
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
