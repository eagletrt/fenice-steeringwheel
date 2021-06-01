import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import "status"

Control {
    id: errors

    // TODO: check
    property var isStarted: false
    property var btnClickable: false
    //    property var errstatus: CarStatus.ERRStatus
    property var ledStates: ['OK', 'NO', 'DEFAULT', 'OUTDATED']
    property var errorsLEDS: [[["APPS", "DEFAULT"], ["BSE", "DEFAULT"], ["STEER", "DEFAULT"]], [["ENCOD L", "DEFAULT"], ["GPS", "DEFAULT"], ["ENCOD R", "DEFAULT"]], [["IMU FR", "DEFAULT"], ["IMU CN", "DEFAULT"], ["IMU RR", "DEFAULT"]]]

    // TODO: check
    function connect() {
        window.buttonClicked.connect(buttonClickedHandler);
    }

    function disconnect() {
        window.buttonClicked.disconnect(buttonClickedHandler);
    }

    function buttonClickedHandler(btnID) {
        if (btnID === 3)
            CAN.sendMarker();

    }

    padding: 20
    // TODO: check protocol
    // TODO: simplify
    //    onErrstatusChanged: {
    //        var newErrStatus = errorsLEDS;
    //        // APPS
    //        newErrStatus[0][0][1] = ledStates[errstatus[0]];
    //        // BSE
    //        newErrStatus[0][1][1] = ledStates[errstatus[1]];
    //        // STEER
    //        newErrStatus[0][2][1] = ledStates[errstatus[4]];
    //        // WHEEL DX
    //        newErrStatus[1][2][1] = ledStates[errstatus[3]];
    //        // WHEEL SX
    //        newErrStatus[1][0][1] = ledStates[errstatus[2]];
    //        // GPS
    //        newErrStatus[1][1][1] = ledStates[errstatus[6]];
    //        // IMU FRONT
    //        newErrStatus[2][0][1] = ledStates[errstatus[5]];
    //        // IMU CENTRAL
    //        newErrStatus[2][1][1] = ledStates[errstatus[7]];
    //        // IMU REAR
    //        newErrStatus[2][2][1] = ledStates[errstatus[8]];
    //        errorsLEDS = newErrStatus;
    //    }
    // TODO: check
    Component.onCompleted: {
        connect();
    }

    contentItem: GridLayout {
        rows: 5
        columns: 3
        rowSpacing: 10
        columnSpacing: 10

        Repeater {
            model: errorsLEDS[0]

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                StatusCard {
                    name: modelData[0]
                    state: ledStates[Math.floor(Math.random() * ledStates.length)] // modelData[1]
                }

            }

        }

        Repeater {
            model: errorsLEDS[1]

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                StatusCard {
                    name: modelData[0]
                    state: ledStates[Math.floor(Math.random() * ledStates.length)] // modelData[1]
                }

            }

        }

        Repeater {
            model: errorsLEDS[2]

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                StatusCard {
                    name: modelData[0]
                    state: ledStates[Math.floor(Math.random() * ledStates.length)] // modelData[1]
                }

            }

        }

    }

}
