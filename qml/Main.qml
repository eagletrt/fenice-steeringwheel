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

            target: Buttons
        }

        Connections {
            function onRace_changed(race) {
                if (stack.currentTab.name !== "telemetry")
                    popper.show(["None", "Cross", "Skidpad", "Endur", "Accel"][race], Style.foreground);

            }

            target: Car.telemetry
        }

        Connections {
            function onMap_changed(map) {
                popper.show(String(map) + "%", Style.foreground);
            }

            function onTraction_control_changed(tractionControl) {
                popper.show(["Off", "Slip", "Torque", "Torque\n&\nSlip"][tractionControl], Style.foreground);
            }

            target: Car.steering
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

        TabStack {
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
