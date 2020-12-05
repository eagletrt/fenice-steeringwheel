import Const 1.0
import QtGraphicalEffects 1.0
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import "components"

Rectangle {
    // introdurre stato active o no per poter
    // gestire il gradient del testo, questa funzionalità va implementata
    // anche della racing page per il superamento di certe soglie da parte
    // dei valori "critici" temperatura, voltaggio e anche la velocità
    // mainwindow.canSwitchPage = false;
    // tabView.stepIntoTab = true;

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
    property var ntest: CarStatus.nTests
    // Number of cells into test section
    property var ndriver: CarStatus.nDrivers
    // Number of cells into driver section
    property var telemetrystatus: CarStatus.TelemetryStatus
    property var tests: [["Acceleration", '1'], ["Skippad", '0'], ["Endurance", '0'], ["Brake", '0'], ["Test", '0']]
    property var drivers: [["Pilotapazzo", '1'], ["Iron512", '0'], ["Pippogas", '0'], ["Nicolareds", '0'], ["Mirco", '0']]

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
                if (tabSelected === 1) {
                    tabSelected = 0;
                    console.log("tab test selected");
                } else {
                    tabSelected = 1;
                    console.log("tab driver selected");
                }
            }
        }
        if (btnID === 3) {
            console.log("send to telemtry");
            CAN.asktelemetry();
        }
        if (btnID === 4 && tabView.stepIntoTab) {
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
        }
        if (btnID === 5 && tabView.stepIntoTab) {
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
        }
    }

    color: Style.transparent
    anchors.fill: parent
    onTelemetrystatusChanged: {
        tabTest.currentIndex = telemetrystatus[0];
        tabDriver.currentIndex = telemetrystatus[1];
    }

    ColumnLayout {
        id: telemetry

        anchors.fill: parent

        TabView {
            id: tabTest

            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            tabPosition: Qt.BottomEdge

            Repeater {
                model: tests

                Tab {
                    Rectangle {
                        color: Style.background

                        Text {
                            anchors.centerIn: parent
                            font: tabSelected === 0 ? Style.sans.h2 : Style.sans.h3
                            color: tabSelected === 0 ? Style.orange : Style.text
                            text: modelData[0]
                        }

                    }

                }

            }

            style: TabViewStyle {
                frameOverlap: 0

                tab: Rectangle {
                    color: Style.background
                    // color: styleData.selected ? "lightgrey" :"black"
                    implicitWidth: tabDriver.width / ntest
                    height: 0
                }

            }

        }

        TabView {
            id: tabDriver

            Layout.alignment: Qt.AlignBottom
            Layout.fillWidth: true
            Layout.fillHeight: true
            tabPosition: Qt.BottomEdge

            Repeater {
                model: drivers

                Tab {
                    Rectangle {
                        color: Style.background

                        Text {
                            anchors.centerIn: parent
                            font: tabSelected === 1 ? Style.sans.h2 : Style.sans.h3
                            color: tabSelected === 1 ? Style.orange : Style.text
                            text: modelData[0]
                        }

                    }

                }

            }

            style: TabViewStyle {
                frameOverlap: 0

                tab: Rectangle {
                    color: Style.background
                    // color: styleData.selected ? "lightgrey" :"black"
                    border.color: Style.foreground
                    border.width: 5
                    implicitWidth: tabDriver.width / ndriver
                    height: 0
                }

            }

        }

    }

    StatusFrame {
    }

}
