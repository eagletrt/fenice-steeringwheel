import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Control {
    id: telemetry

    property int selected: -1
    property var tests: [["Acceleration", '1'], ["Skippad", '0'], ["Endurance", '0'], ["Brake", '0'], ["Test", '0']]
    property var drivers: [["Pilotapazzo", '1'], ["Iron512", '0'], ["Pippogas", '0'], ["Nicolareds", '0'], ["Mirco", '0']]
    property var racetracks: [["Demo", "qrc:/qml/img/racetracks/demo.png", "1"], ["Demo Rot", "qrc:/qml/img/racetracks/demo_rot.png", "2"]]
    readonly property int testsId: 0
    readonly property int driversId: 1
    readonly property int racetracksId: 2

    function connect() {
        window.buttonClicked.connect(buttonClicked);
    }

    function disconnect() {
        window.buttonClicked.disconnect(buttonClicked);
    }

    function buttonClicked(button) {
        if (button === ButtonIds.buttonTopLeft) {
            if (tabs.blocked) {
                tabs.blocked = false;
                selected = -1;
            }
        }
        if (button === ButtonIds.buttonTopRight) {
            if (!tabs.blocked)
                tabs.blocked = true;

            selected = (selected + 1) % 3;
        }
        if (button === ButtonIds.buttonBottomRight)
            CAN.asktelemetry();

        if ((button === ButtonIds.paddleBottomLeft || button === ButtonIds.paddleBottomRight) && tabs.blocked) {
            const step = button === ButtonIds.paddleBottomRight ? 1 : -1;
            let component, model;
            if (selected === testsId) {
                component = boxTest;
                model = tests;
            } else if (selected === driversId) {
                component = boxDriver;
                model = drivers;
            } else if (selected === racetracksId) {
                component = boxRacetrack;
                model = racetracks;
            }
            let value = Utils.mod(component.currentIndex + step, model.length);
            component.currentIndex = value;
            if (selected === testsId)
                CarStatus.setTest(value);
            else if (selected === driversId)
                CarStatus.setDriver(value);
            else if (selected === racetracksId)
                CarStatus.setDriver(value); // TODO: create Carstatus.setRacetrack method
        }
    }

    padding: 20

    contentItem: GridLayout {
        rows: 2
        columns: 2
        rowSpacing: 10
        columnSpacing: 10

        Rectangle {
            color: selected === 0 ? Style.yellow : Style.surface
            Layout.row: 0
            Layout.column: 0
            Layout.fillHeight: true
            Layout.fillWidth: true

            StackLayout {
                id: boxTest

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
            color: selected === 1 ? Style.yellow : Style.surface
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout {
                id: boxDriver

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
            color: selected === 2 ? Style.yellow : Style.surface
            Layout.row: 0
            Layout.column: 1
            Layout.rowSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout {
                id: boxRacetrack

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
