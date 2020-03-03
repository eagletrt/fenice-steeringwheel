import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: backgroundTelemetry
    color: "black"
    anchors.fill: parent
    FontLoader {id:blackops; source: "../lib/blops.ttf"}

    property var tabSelected: -1
    property var stepIntoTabTest: false
    property var stepIntoTabDriver: false
    property var selectedIndexTest: -1
    property var selectedIndexDriver: -1 
    property var test: 0 
    property var driver: 1
    //ATTENTION: In order to add or remove tests or drivers
    //remember to change the appropriate constant value in telemetry.h
    //because nTests and nDrivers, to maintain consistency in data,
    //acheive their value from there
    property var ntest: CarStatus.nTests //Number of cells into test section
    property var ndriver: CarStatus.nDrivers //Number of cells into driver section
    property var telemetrystatus: CarStatus.TelemetryStatus

    property var tests: [ 
       ["acceleration", '1'],
       ["skippad", '0'],
       ["endurance", '0'],
       ["brake", '0'],
       ["test", '0'],
    ]

    property var drivers: [
       ["pilotapazzo", '1'],
       ["iron512", '0'],
       ["pippogas", '0'],
       ["nicolareds", '0'],
       ["mirco", '0'],
    ]

    onTelemetrystatusChanged: {
        tabTest.currentIndex = telemetrystatus[0];
        tabDriver.currentIndex = telemetrystatus[1];
    }

    function connect() {
        menu.btnClicked.connect(btnClickedHandler);
    }
    function disconnect() {
        menu.btnClicked.disconnect(btnClickedHandler);
    }

    function btnClickedHandler(btnID) {
        if (btnID == 0){
            if (tabView.stepIntoTab) {
                tabView.stepIntoTab = false;
                mainwindow.canSwitchPage = true;
                tabSelected = -1
                console.log("tab exit")
                }
            } else {
                // mainwindow.canSwitchPage = false;
                // tabView.stepIntoTab = true;
            }
        if (btnID == 2){
            if (!tabView.stepIntoTab) {
                tabView.stepIntoTab = true;
                mainwindow.canSwitchPage = false;
                console.log("entered in tab")
                console.log("tab test selected")
                tabSelected = 0
            } else {
                if(tabSelected == 1){
                    tabSelected = 0
                    console.log("tab test selected")
                } else {
                    tabSelected = 1
                    console.log("tab driver selected")
                }
            }
        }
        if (btnID == 3) {
            console.log("send to telemtry");
            CAN.asktelemetry();
        }
        if (btnID == 4  && tabView.stepIntoTab) {
            if(tabSelected == 0){
                console.log("tabTest index: " + tabTest.currentIndex)
                mainwindow.canSwitchPage = false;
                if (tabTest.currentIndex == 0){
                    tabTest.currentIndex = (ntest-1);
                } else {
                    tabTest.currentIndex--;
                }

                CarStatus.setTest(tabTest.currentIndex) 
            }
            if(tabSelected == 1){
                console.log("tabDriver index: " + tabDriver.currentIndex)
                mainwindow.canSwitchPage = false;
                if (tabDriver.currentIndex == 0) {
                    tabDriver.currentIndex = (ndriver-1);
                } else {
                    tabDriver.currentIndex--;
                }

                CarStatus.setDriver(tabDriver.currentIndex)
            }
        }
        if (btnID == 5 && tabView.stepIntoTab) {
            if(tabSelected == 0){
                console.log("tabTest index: " + tabTest.currentIndex)
                mainwindow.canSwitchPage = false;
                if (tabTest.currentIndex == (ntest-1)) {
                    tabTest.currentIndex = 0;
                } else {
                    tabTest.currentIndex++;
                }

                CarStatus.setTest(tabTest.currentIndex) 
            }
            if(tabSelected == 1){
                console.log("tabDriver index: " + tabDriver.currentIndex)
                mainwindow.canSwitchPage = false;
                tabDriver.currentIndex = (tabDriver.currentIndex + 1) % ndriver

                CarStatus.setDriver(tabDriver.currentIndex) 
            }
        }
    }

    ColumnLayout{
        id: telemetry
        anchors.fill: parent

        TabView {
            id: tabTest
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            tabPosition: Qt.BottomEdge
            // property var stepIntoTab: false
            Tab {
                id: test0
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==0 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==0 ? "yellow" :"lightgrey"
                        text: tests[0][0]
                    }
                }
            }
            Tab {
                id: test1
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==0 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==0 ? "yellow" :"lightgrey"
                        text: tests[1][0]
                    }
                }
            }
            Tab {
                id: test2
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==0 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==0 ? "yellow" :"lightgrey"
                        text: tests[2][0]
                    }
                }
            }
            Tab {
                id: test3
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==0 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==0 ? "yellow" :"lightgrey"
                        text: tests[3][0]
                    }
                }
            }
            Tab {
                id: test4
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==0 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==0 ? "yellow" :"lightgrey"
                        text: tests[4][0]
                    }
                }
            }

            style: TabViewStyle {
                frameOverlap: 0
                tab: Rectangle {
                    color: "black"
                    // color: styleData.selected ? "lightgrey" :"black"
                    implicitWidth: tabDriver.width/ntest
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
            // property var stepIntoTab: false
            Tab {
                id: driver0
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==1 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==1 ? "yellow" :"lightgrey"
                        text: drivers[0][0]
                    }
                }
            }
            Tab {
                id: driver1
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==1 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==1 ? "yellow" :"lightgrey"
                        text: drivers[1][0]
                    }
                }
            }
            Tab {
                id: driver2
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==1 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==1 ? "yellow" :"lightgrey"
                        text: drivers[2][0]
                    }
                }
            }
            Tab {
                id: driver3
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==1 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==1 ? "yellow" :"lightgrey"
                        text: drivers[3][0]
                    }
                }
            }
            Tab {
                id: driver4
                Rectangle { 
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: tabSelected==1 ? 60 : 45
                        font.family: blackops.name
                        color: tabSelected==1 ? "yellow" :"lightgrey"
                        text: drivers[4][0]
                    }
                }
            }
            style: TabViewStyle {
                frameOverlap: 0
                tab: Rectangle {
                    color: "black"
                    // color: styleData.selected ? "lightgrey" :"black"
                    implicitWidth: tabDriver.width/ndriver
                    height: 0
                }
            }
        }

        }
}