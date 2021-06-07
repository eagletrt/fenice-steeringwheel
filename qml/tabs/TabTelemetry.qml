import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Control {
    id: telemetry

    property int tabSelected: -1
    property bool stepIntoTabTest: false
    property bool stepIntoTabDriver: false
    property int selectedIndexTest: -1
    property int selectedIndexDriver: -1
    property int test: 0
    property int driver: 1
    // ATTENTION: In order to add or remove tests or drivers
    // remember to change the appropriate constant value in telemetry.h
    // because nTests and nDrivers, to maintain consistency in data,
    // acheive their value from there
    // Number of cells into test section
    property var ntest: tests.length
    // Number of cells into driver section
    property var ndriver: drivers.length
    //    property var telemetrystatus: CarStatus.TelemetryStatus
    property var tests: [["Acceleration", '1'], ["Skippad", '0'], ["Endurance", '0'], ["Brake", '0'], ["Test", '0']]
    property var drivers: [["Pilotapazzo", '1'], ["Iron512", '0'], ["Pippogas", '0'], ["Nicolareds", '0'], ["Mirco", '0']]
    property var racetracks: [["Demo", "qrc:/qml/img/racetracks/demo.png", "1"], ["Demo Rot", "qrc:/qml/img/racetracks/demo_rot.png", "2"]]

    function connect() {
        window.buttonClicked.connect(buttonClickedHandler);
    }

    function disconnect() {
        window.buttonClicked.disconnect(buttonClickedHandler);
    }

    function buttonClickedHandler(btnID) {
        if (btnID === 0) {
            if (tabs.blocked) {
                tabs.blocked = false;
                window.canSwitchPage = true;
                tabSelected = -1;
                console.log("tab exit");
            }
        } else {
        }
        if (btnID === 2) {
            if (!tabs.blocked) {
                tabs.blocked = true;
                window.canSwitchPage = false;
                console.log("entered in tab");
                console.log("tab test selected");
                tabSelected = 0;
            } else {
                tabSelected = (tabSelected + 1) % 3;
                console.log(tabSelected);
            }
        }
        if (btnID === 3) {
            console.log("send to telemtry");
            CAN.asktelemetry();
        }
        if (btnID === 4 && tabs.blocked) {
            if (tabSelected === 0) {
                console.log("tabTest index: " + tabTest.currentIndex);
                window.canSwitchPage = false;
                if (tabTest.currentIndex === 0)
                    tabTest.currentIndex = (ntest - 1);
                else
                    tabTest.currentIndex--;
                CarStatus.setTest(tabTest.currentIndex);
            }
            if (tabSelected === 1) {
                console.log("tabDriver index: " + tabDriver.currentIndex);
                window.canSwitchPage = false;
                if (tabDriver.currentIndex === 0)
                    tabDriver.currentIndex = (ndriver - 1);
                else
                    tabDriver.currentIndex--;
                CarStatus.setDriver(tabDriver.currentIndex);
            }
            if (tabSelected === 2) {
                console.log("tabRacetrack index: " + tabRacetracks.currentIndex);
                window.canSwitchPage = false;
                if (tabRacetracks.currentIndex === 0)
                    tabRacetracks.currentIndex = (racetracks.length - 1);
                else
                    tabRacetracks.currentIndex--;
            }
        }
        if (btnID === 5 && tabs.blocked) {
            if (tabSelected === 0) {
                console.log("tabTest index: " + tabTest.currentIndex);
                window.canSwitchPage = false;
                if (tabTest.currentIndex === (ntest - 1))
                    tabTest.currentIndex = 0;
                else
                    tabTest.currentIndex++;
                CarStatus.setTest(tabTest.currentIndex);
            }
            if (tabSelected === 1) {
                console.log("tabDriver index: " + tabDriver.currentIndex);
                window.canSwitchPage = false;
                tabDriver.currentIndex = (tabDriver.currentIndex + 1) % ndriver;
                CarStatus.setDriver(tabDriver.currentIndex);
            }
            if (tabSelected === 2) {
                console.log("tabRacetrack index: " + tabRacetracks.currentIndex);
                window.canSwitchPage = false;
                tabRacetracks.currentIndex = (tabRacetracks.currentIndex + 1) % racetracks.length;
            }
        }
    }

    padding: 20

    contentItem: GridLayout {
        rows: 2
        columns: 2
        rowSpacing: 10
        columnSpacing: 10

        Rectangle {
            color: tabSelected === 0 ? Style.yellow : Style.surface
            Layout.row: 0
            Layout.column: 0
            Layout.fillHeight: true
            Layout.fillWidth: true

            StackLayout {
                id: tabTest

                anchors.fill: parent

                Repeater {
                    model: tests

                    Item {
                        Text {
                            anchors.centerIn: parent
                            font: Style.sans.h2
                            color: Style.textInverted
                            text: modelData[0]
                        }

                    }

                }

            }

        }

        Rectangle {
            color: tabSelected === 1 ? Style.yellow : Style.surface
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout {
                id: tabDriver

                anchors.fill: parent

                Repeater {
                    model: drivers

                    Item {
                        Text {
                            anchors.centerIn: parent
                            font: Style.sans.h2
                            color: Style.textInverted
                            text: modelData[0]
                        }

                    }

                }

            }

        }

        Rectangle {
            color: tabSelected === 2 ? Style.yellow : Style.surface
            Layout.row: 0
            Layout.column: 1
            Layout.rowSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout {
                id: tabRacetracks

                anchors.fill: parent

                Repeater {
                    model: racetracks

                    ColumnLayout {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Item {
                            Layout.fillWidth: true
                            Layout.minimumHeight: childrenRect.height + 40

                            Text {
                                anchors.centerIn: parent
                                font: Style.sans.h2
                                color: Style.textInverted
                                text: modelData[0]
                            }

                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Image {
                                anchors.margins: 20
                                anchors.fill: parent
                                fillMode: Image.PreserveAspectFit
                                source: modelData[1]
                            }

                        }

                    }

                }

            }

        }

    }

}
