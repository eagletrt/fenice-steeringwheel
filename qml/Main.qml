import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: main

    width: Style.width
    maximumWidth: Style.width
    minimumWidth: Style.width
    height: Style.height
    maximumHeight: Style.height
    minimumHeight: Style.height
    visible: true
    title: qsTr("Steering Wheel")

    Item {
        id: window

        // Buttons signals
        signal buttonPressed(int button)
        signal buttonReleased(int button)
        // Steering signals
        signal logsChanged(string line)

        anchors.fill: parent

        Connections {
            function onButton_pressed(button) {
                window.buttonPressed(button);
            }

            function onButton_released(button) {
                window.buttonReleased(button);
            }

            function onManettino_left_changed(value) {
                if (!Car.steering.debug_mode) {
                    popper.show("SLIP\n" + String(Car.steering.sc_values[value] * 10) + "%", Style.foreground);
                } else {
                    if (value > 5)
                        return ;

                    popper.show(["Pumps Auto", "Pumps Off", "Pumps 25%", "Pumps 50%", "Pumps 75%", "Pumps 100%"][value], Style.foreground);
                }
            }

            function onManettino_center_changed(value) {
                if (!Car.steering.debug_mode) {
                    popper.show("TORQUE\n" + String(Car.steering.tv_values[value] * 10) + "%", Style.foreground);
                } else {
                    if (value > 5)
                        return ;

                    popper.show(["Radiat Auto", "Radiat Off", "Radiat 25%", "Radiat 50%", "Radiat 75%", "Radiat 100%"][value], Style.foreground);
                }
            }

            function onManettino_right_changed(value) {
                popper.show("POWER MAP\n" + String(Car.steering.pm_values[value] * 10) + "%", Style.foreground);
            }

            target: Buttons
        }

        Connections {
            function onLogs_changed(line) {
                window.logsChanged(line);
            }

            target: Global
        }

        Connections {
            function onShow_popup(message, color) {
                popper.show(message, color);
            }

            target: Car
        }

        Switcher {
            id: stack

            anchors.fill: parent
            Component.onCompleted: {
                connect();
            }
        }

        Popper {
            id: popper

            anchors.centerIn: parent
        }

    }

}
