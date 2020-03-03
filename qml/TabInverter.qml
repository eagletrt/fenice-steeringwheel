import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    anchors.fill: parent

    color: "#000000"

    property int currentSelected: -1
    property var canHvStatus: CarStatus.HVStatus
    property var hvPossibleStates: ["NO", "OK", "DEFAULT"]
    property var hvStatus: [
        ["preCharge", "DEFAULT", false],
        ["Inverter Left", "DEFAULT", false],
        ["Inverter Right", "DEFAULT", false]
    ]

    function connect() {
        // console.log("Tab connessa - Inverter");
        menu.btnClicked.connect(btnClickedHandler);
    }

    function disconnect() {
        // console.log("Tab disconnessa - Inverter");
        menu.btnClicked.disconnect(btnClickedHandler);
    }

    onCanHvStatusChanged: {
        var newHvStatus = hvStatus;

        newHvStatus[0][1] = hvPossibleStates[canHvStatus[0]];
        newHvStatus[1][1] = hvPossibleStates[canHvStatus[1]];
        newHvStatus[2][1] = hvPossibleStates[canHvStatus[2]];

        hvStatus = newHvStatus;
    }

    function btnClickedHandler(btnID) {
        if (btnID == 2) {
            // Step into this tab and change the behaviour of btnID
            if (!tabView.stepIntoTab) {
                tabView.stepIntoTab = true;
                // Prevent the button 0 to switch to Racing Page!
                mainwindow.canSwitchPage = false;

                var newHvStatus = hvStatus;

                // Select the first element
                currentSelected += 1;
                // Select the new current row
                newHvStatus[currentSelected][2] = true;

                // Force trigger of the model change
                hvStatus = newHvStatus;
            } else {
                var newHvStatus = hvStatus;

                // Deselect the current selected
                newHvStatus[currentSelected][2] = false;
                // Increase the current selected row

                if (currentSelected == 2) {
                    currentSelected = 0;
                } else {
                    currentSelected += 1;
                }

                // Select the new current row
                newHvStatus[currentSelected][2] = true;

                // Force trigger of the model change
                hvStatus = newHvStatus;
            }
        }

        if (btnID == 1) {
            if (!mainwindow.canSwitchPage) {
                CAN.askHVUpdate(currentSelected);
            }
        }

        if (btnID == 0) {
            if (tabView.stepIntoTab) {
                var newHvStatus = hvStatus;

                // Select the new current row
                newHvStatus[currentSelected][2] = false;

                // Force trigger of the model change
                hvStatus = newHvStatus;

                currentSelected = -1;

                // Restore Button 0 initial handler
                mainwindow.canSwitchPage = true;

                tabView.stepIntoTab = false;
            }
        }

        if (btnID == 3){
            CAN.sendMarker();
        }
    }

    GridLayout {
        id: grid1
        anchors.fill: parent
        columns: 1
        rows: 3

        Repeater {
            model: hvStatus
            delegate: HVStatusLED {
                text: modelData[0]
                state: modelData[1]
                selected: modelData[2]
                Layout.preferredWidth: root.width / 1
                Layout.preferredHeight: root.height / 3
            }
        }
    }
}
