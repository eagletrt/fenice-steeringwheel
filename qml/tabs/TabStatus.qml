import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"
import "status"

Control {
    id: status

    property var btnClickable: true
    property var isStarted: false
    property var isStopped: true
    property var canstatus: CarStatus.CANStatus
    property var ledStates: ['DEFAULT', 'OUTDATED']
    property var canLeds: [["InvRight", 'CAN_DEFAULT'], ["InvLeft", 'CAN_DEFAULT'], ["STMFront", 'CAN_DEFAULT'], ["STMCentral", 'CAN_DEFAULT'], ["STMPedals", 'CAN_DEFAULT'], ["STMRear", 'CAN_DEFAULT'], ["BMS HV", 'CAN_DEFAULT'], ["BMS LV", 'CAN_DEFAULT']]

    function connect() {
        mainwindow.btnClicked.connect(btnClickedHandler);
    }

    function disconnect() {
        mainwindow.btnClicked.disconnect(btnClickedHandler);
    }

    function btnClickedHandler(btnID) {
        tabView.stepIntoTab = true;
        if (btnID === 0) {
        }
        if (btnID === 1) {
            CAN.askSetupOrIdle(1);
            console.log("Asking to go from IDLE to Setup");
        }
        if (btnID === 2) {
            if (!tabView.stepIntoTab) {
                // Prevent the button 0 to switch to Racing Page!
                tabView.stepIntoTab = true;
            } else {
                console.log("Asking to go from Setup to Idle");
                // CAN.checkCANCommunication(false);
                // CarStatus.stopMessage(2);
                CAN.askSetupOrIdle(0);
            }
        }
        if (btnID === 3)
            CAN.sendMarker();

        tabView.stepIntoTab = false;
    }

    anchors.fill: parent
    padding: 20
    onCanstatusChanged: {
        // console.log("Cambiato il CAN Status da Centralina");
        var newCanLeds = canLeds;
        for (var i = 0; i < canstatus.length; i++) {
            newCanLeds[i][1] = ledStates[canstatus[i]];
        }
        canLeds = newCanLeds;
    }

    contentItem: ColumnLayout {
        spacing: 10

        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            rows: 5
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Repeater {
                model: canLeds

                delegate: Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    StatusCard {
                        name: modelData[0]
                        state: ledStates[Math.floor(Math.random() * ledStates.length)] // modelData[1]
                    }

                }

            }

        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 5
            color: Style.dark
        }

        RowLayout {
            spacing: 10
            Layout.fillWidth: true
            Layout.fillHeight: true

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 80

                StatusCard {
                    name: "START"
                    state: "OK"
                }

            }

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 80

                StatusCard {
                    name: "STOP"
                    state: "NO"
                }

            }

        }

    }

}
