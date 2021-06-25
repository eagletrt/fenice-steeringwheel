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

        property bool canSwitchPage: true

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

        Connections {
            function onShowPopup(line) {
                popupText.text = line;
                popupAnimation.start();
            }

            target: CarStatus
        }

        SequentialAnimation {
            id: popupAnimation

            running: false
            onStarted: {
            }
            onStopped: {
            }

            ParallelAnimation {
                PropertyAnimation {
                    target: popup
                    properties: "visible"
                    from: false
                    to: true
                    duration: 0
                }

            }

            ParallelAnimation {
                PropertyAnimation {
                    target: popup
                    properties: "visible"
                    from: true
                    to: false
                    duration: 550
                }

            }

        }

        MenuPage {
            anchors.fill: parent
            Component.onCompleted: {
                connect();
            }
        }

        Rectangle {
            id: popup

            anchors.centerIn: parent
            color: Style.foreground
            radius: 10
            visible: false
            width: 500
            height: 240

            Text {
                id: popupText

                anchors.centerIn: parent
                color: Style.textInverted
                font: Style.mono.verybig
            }

        }

    }

}
