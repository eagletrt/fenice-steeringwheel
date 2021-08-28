import Car 1.0
import Const 1.0
import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

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
            function onButtonPressed(button) {
                window.buttonPressed(button);
            }

            function onButtonReleased(button) {
                window.buttonReleased(button);
            }

            target: Buttons
        }

        Connections {
            function onRaceChanged(race) {
                if (stack.currentTab.name !== "telemetry")
                    popper.show(["default", "Cross", "Skidpad", "Endur", "Accel"][race]);

            }

            target: Car.telemetry
        }

        Connections {
            function onMapChanged(map) {
                popper.show(String(map) + "%");
            }

            function onTractionControlChanged(tractionControl) {
                popper.show(["OFF", "S", "T", "T&S"][tractionControl]);
            }

            target: Car.steering
        }

        Connections {
            function onLogsChanged(line) {
                window.logsChanged(line);
            }

            target: Global
        }

        Connections {
            function onShowPopup(message) {
                popper.show(message);
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
