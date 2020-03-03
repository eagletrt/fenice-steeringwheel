import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: errors
    anchors.fill: parent
    color: "#000000"

    property var isStarted: false
    property var btnClickable: false
    property var errstatus: CarStatus.ERRStatus
    property var ledStates: ['OK', 'NO', 'DEFAULT'];

	function connect() {
        // console.log("Tab connessa - Errors");
        mainwindow.btnClicked.connect(btnClickedHandler);
    }

    function disconnect() {
        // console.log("Tab disconnessa - Errors");
        mainwindow.btnClicked.disconnect(btnClickedHandler);
    }

    onErrstatusChanged: {
        // console.log("Cambiato ERR Status da Centralina");

        var newErrStatus = errorsLEDS;

        // console.log(errorsLEDS);

        // APPS
        newErrStatus[0][0][1] = ledStates[errstatus[0]];
        // BSE
        newErrStatus[0][1][1] = ledStates[errstatus[1]];
        // STEER
        newErrStatus[0][2][1] = ledStates[errstatus[4]];

        // WHEEL DX
        newErrStatus[1][2][1] = ledStates[errstatus[3]];
        // WHEEL SX
        newErrStatus[1][0][1] = ledStates[errstatus[2]];
        // GPS
        newErrStatus[1][1][1] = ledStates[errstatus[6]];


        // IMU FRONT
        newErrStatus[2][0][1] = ledStates[errstatus[5]];
        // IMU CENTRAL
        newErrStatus[2][1][1] = ledStates[errstatus[7]];
        // IMU REAR
        newErrStatus[2][2][1] = ledStates[errstatus[8]];

        errorsLEDS = newErrStatus;
    }

    function btnClickedHandler(btnID) {
        if (btnID == 3){
            CAN.sendMarker();
        }
        if (btnID == 2) {
            /*
            // Step into this tab and change the behaviour of btnID
            if (!tabView.stepIntoTab) {
                // Set the button clickable
                btnClickable = true;
                isStarted = false;

                // Prevent the button 0 to switch to Racing Page!
                tabView.stepIntoTab = true;
                mainwindow.canSwitchPage = false;

            } else {
                if (!isStarted) {
                    // Update the errors
                    isStarted = true;
                    console.log("Update Errors");
                    CAN.checkSensorsError();
                }

                // Set the button again to be not clickable
                btnClickable = false;

                // Restore Button 0 initial handler
                mainwindow.canSwitchPage = true;
                tabView.stepIntoTab = false;
            }
            */
        }
    }

	property var errorsLEDS: [
        [
            ["APPS", "DEFAULT"],
            ["BSE", "DEFAULT"],
            ["Steer", "DEFAULT"]
        ],
        [
            ["ENCOD L", "DEFAULT"],
            ["GPS", "DEFAULT"],
            ["ENCOD R", "DEFAULT"]
        ],
        [
            ["IMU FR", "DEFAULT"],
            ["IMU CN", "DEFAULT"],
            ["IMU RR", "DEFAULT"]
        ]
	]

    GridLayout {
        columns: 3
        rows: 4
        columnSpacing: 0
        rowSpacing: 0
        anchors.fill: parent

        Repeater {
            model: errorsLEDS[0]
            CANStatusLED {
                text: modelData[0]
                state: modelData[1]
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: errors.height / 4
            }
        }

        Repeater {
            model: errorsLEDS[1]
            CANStatusLED {
                text: modelData[0]
                state: modelData[1]
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: errors.height / 4
            }
        }

        Repeater {
            model: errorsLEDS[2]
            CANStatusLED {
                text: modelData[0]
                state: modelData[1]
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: errors.height / 4
            }
        }

        /*Rectangle {
            Layout.preferredWidth: errors.width
            Layout.preferredHeight: errors.height / 6
            Layout.columnSpan: 3
            color: "#000000"

            Button {
                state: !btnClickable ? 'IDLE' : 'SELECTED'
                activeColor: "blue"
                text: "UPDATE"
            }
        }*/
    }
}
