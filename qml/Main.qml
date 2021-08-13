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
        signal buttonClicked(int button)
        signal carStatusChanged(int status)
        signal mapChanged(int map)
        // Steering signals
        signal logsChanged(string line)
        // CAN Signals
        signal controlStateChanged(int ctrlIsEnabled, int ctrlIsOn, int warning, int error)
        signal hvStatusChanged(int invRight, int invLeft, int preCharge)

        anchors.fill: parent

        Connections {
            function onButtonClicked(button) {
                window.buttonClicked(button);
            }

            function onButtonPressed(button) {
                window.buttonPressed(button);
            }

            function onButtonReleased(button) {
                window.buttonReleased(button);
            }

            function onMapChanged(map) {
                window.mapChanged(map);
            }

            target: Buttons
        }

        Connections {
            function onLogsChanged(line) {
                window.logsChanged(line);
            }

            target: Steering
        }

        TabStack {
            anchors.fill: parent
            Component.onCompleted: {
                connect();
            }
        }

        Popup {
        }

    }

}
