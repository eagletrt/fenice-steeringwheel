import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: errors
    anchors.fill: parent
    // color: "transparent"
    color: "#000000"

    property var isStarted: false
    property var btnClickable: false
    property var errstatus: CarStatus.ERRStatus
    property var ledStates: ['OK', 'NO', 'DEFAULT'];

	function connect() {
        mainwindow.btnClicked.connect(btnClickedHandler);
    }

    function disconnect() {
        mainwindow.btnClicked.disconnect(btnClickedHandler);
    }

    onErrstatusChanged: {
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
    }

    Component.onCompleted: {
        connect();
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
    }
}
