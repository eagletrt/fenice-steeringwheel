import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12
import "components"

Control {
    // introdurre stato active o no per poter
    // gestire il gradient del testo, questa funzionalità va implementata
    // anche della racing page per il superamento di certe soglie da parte
    // dei valori "critici" temperatura, voltaggio e anche la velocità
    // mainwindow.canSwitchPage = false;
    // tabView.stepIntoTab = true;
    //    StatusFrame {
    //    }
    id: backgroundTelemetry

    property var tabSelected: -1
    property var stepIntoTabTest: false
    property var stepIntoTabDriver: false
    property var selectedIndexTest: -1
    property var selectedIndexDriver: -1
    property var test: 0
    property var driver: 1
    // ATTENTION: In order to add or remove tests or drivers
    // remember to change the appropriate constant value in telemetry.h
    // because nTests and nDrivers, to maintain consistency in data,
    // acheive their value from there
    // Number of cells into test section
    property var ntest: CarStatus.nTests
    // Number of cells into driver section
    property var ndriver: CarStatus.nDrivers
    property var telemetrystatus: CarStatus.TelemetryStatus
    property var tests: [["Acceleration", '1'], ["Skippad", '0'], ["Endurance", '0'], ["Brake", '0'], ["Test", '0']]
    property var drivers: [["Pilotapazzo", '1'], ["Iron512", '0'], ["Pippogas", '0'], ["Nicolareds", '0'], ["Mirco", '0']]
    property var racetracks: [["Demo", "qrc:/qml/img/racetracks/demo.png", "1"], ["Demo Rot", "qrc:/qml/img/racetracks/demo_rot.png", "2"]]

    function connect() {
        menu.btnClicked.connect(btnClickedHandler);
    }

    function disconnect() {
        menu.btnClicked.disconnect(btnClickedHandler);
    }

    function btnClickedHandler(btnID) {
        if (btnID === 0) {
            if (tabView.stepIntoTab) {
                tabView.stepIntoTab = false;
                mainwindow.canSwitchPage = true;
                tabSelected = -1;
                console.log("tab exit");
            }
        } else {
        }
        if (btnID === 2) {
            if (!tabView.stepIntoTab) {
                tabView.stepIntoTab = true;
                mainwindow.canSwitchPage = false;
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
        if (btnID === 4 && tabView.stepIntoTab) {
            // CarStatus.setRacetrack(tabRacetrack.currentIndex);

            if (tabSelected === 0) {
                console.log("tabTest index: " + tabTest.currentIndex);
                mainwindow.canSwitchPage = false;
                if (tabTest.currentIndex === 0)
                    tabTest.currentIndex = (ntest - 1);
                else
                    tabTest.currentIndex--;
                CarStatus.setTest(tabTest.currentIndex);
            }
            if (tabSelected === 1) {
                console.log("tabDriver index: " + tabDriver.currentIndex);
                mainwindow.canSwitchPage = false;
                if (tabDriver.currentIndex === 0)
                    tabDriver.currentIndex = (ndriver - 1);
                else
                    tabDriver.currentIndex--;
                CarStatus.setDriver(tabDriver.currentIndex);
            }
            if (tabSelected === 2) {
                console.log("tabRacetrack index: " + tabRacetracks.currentIndex);
                mainwindow.canSwitchPage = false;
                if (tabRacetracks.currentIndex === 0)
                    tabRacetracks.currentIndex = (racetracks.length - 1);
                else
                    tabRacetracks.currentIndex--;
            }
        }
        if (btnID === 5 && tabView.stepIntoTab) {
            // CarStatus.setRacetrack(tabRacetrack.currentIndex);

            if (tabSelected === 0) {
                console.log("tabTest index: " + tabTest.currentIndex);
                mainwindow.canSwitchPage = false;
                if (tabTest.currentIndex === (ntest - 1))
                    tabTest.currentIndex = 0;
                else
                    tabTest.currentIndex++;
                CarStatus.setTest(tabTest.currentIndex);
            }
            if (tabSelected === 1) {
                console.log("tabDriver index: " + tabDriver.currentIndex);
                mainwindow.canSwitchPage = false;
                tabDriver.currentIndex = (tabDriver.currentIndex + 1) % ndriver;
                CarStatus.setDriver(tabDriver.currentIndex);
            }
            if (tabSelected === 2) {
                console.log("tabRacetrack index: " + tabRacetracks.currentIndex);
                mainwindow.canSwitchPage = false;
                tabRacetracks.currentIndex = (tabRacetracks.currentIndex + 1) % racetracks.length;
            }
        }
    }

    anchors.fill: parent
    onTelemetrystatusChanged: {
        tabTest.currentIndex = telemetrystatus[0];
        tabDriver.currentIndex = telemetrystatus[1];
    }
    padding: 20

    contentItem: GridLayout {
        rows: 2
        columns: 2
        rowSpacing: 10
        columnSpacing: 10

        Rectangle {
//            color: tabSelected === 0 ? Style.red : Style.surface
            color: Style.surface
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
//                            color: Style.text

                            color: tabSelected === 0 ? Style.red : Style.text
                            text: modelData[0]
                        }

                    }

                }

            }

        }

        Rectangle {
//            color: tabSelected === 1 ? Style.red : Style.surface
            color: Style.surface
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
//                            color: Style.text
                            color: tabSelected === 1 ? Style.red : Style.text
                            text: modelData[0]
                        }

                    }

                }

            }

        }

        Rectangle {
//            color: tabSelected === 2 ? Style.red : Style.surface
            color: Style.surface
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
                                font: Style.sans.h3
//                                color: Style.text
                                color: tabSelected === 2 ? Style.red : Style.text
                                text: modelData[0]
                            }

                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Image {
                                id: track
                                anchors.margins: 20
                                anchors.fill: parent
                                fillMode: Image.PreserveAspectFit
                                source: modelData[1]
                            }

                            ColorOverlay {
                                anchors.fill: track
                                source: track
                                color: tabSelected === 2 ? Style.red : Style.transparent
                            }

                        }

                    }

                }

            }

        }

    }

}
