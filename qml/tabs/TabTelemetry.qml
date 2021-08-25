import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Control {
    id: telemetry

    property var races: Car.telemetry.races
    property var pilots: Car.telemetry.pilots
    property var circuits: Car.telemetry.circuits
    property int selected: -1
    readonly property int raceId: 0
    readonly property int pilotId: 1
    readonly property int circuitId: 2

    function connect() {
        window.buttonReleased.connect(onButtonReleased);
    }

    function disconnect() {
        window.buttonReleased.disconnect(onButtonReleased);
    }

    function onButtonReleased(button) {
        if (button === Input.buttonTopLeft) {
            if (tabs.blocked) {
                tabs.blocked = false;
                selected = -1;
            }
        }
        if (button === Input.buttonTopRight) {
            if (!tabs.blocked)
                tabs.blocked = true;

            selected = (selected + 1) % 3;
        }
        if ((button === Input.paddleBottomLeft || button === Input.paddleBottomRight) && tabs.blocked) {
            const step = button === Input.paddleBottomRight ? 1 : -1;
            let component, model;
            if (selected === raceId) {
                component = boxRace;
                model = races;
            } else if (selected === pilotId) {
                component = boxPilot;
                model = pilots;
            } else if (selected === circuitId) {
                component = boxCircuit;
                model = circuits;
            }
            const value = Utils.mod(component.currentIndex + step, model.length);
            component.currentIndex = value;
            if (selected === raceId)
                Car.telemetry.race = value;
            else if (selected === pilotId)
                Car.telemetry.pilot = value;
            else if (selected === circuitId)
                Car.telemetry.circuit = value;
        }
    }

    padding: 20

    contentItem: GridLayout {
        rows: 2
        columns: 2
        rowSpacing: 10
        columnSpacing: 10

        Rectangle {
            color: selected === raceId ? Style.red : Style.surface
            Layout.row: 0
            Layout.column: 0
            Layout.fillHeight: true
            Layout.fillWidth: true

            StackLayout {
                id: boxRace

                anchors.fill: parent

                Repeater {
                    model: races

                    Item {
                        Text {
                            anchors.centerIn: parent
                            font: Style.sans.h2
                            color: Style.textInverted
                            text: modelData.name
                        }

                    }

                }

            }

        }

        Rectangle {
            color: selected === pilotId ? Style.red : Style.surface
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout {
                id: boxPilot

                anchors.fill: parent

                Repeater {
                    model: pilots

                    Item {
                        Text {
                            anchors.centerIn: parent
                            font: Style.sans.h2
                            color: Style.textInverted
                            text: modelData.name
                        }

                    }

                }

            }

        }

        Rectangle {
            color: selected === circuitId ? Style.red : Style.surface
            Layout.row: 0
            Layout.column: 1
            Layout.rowSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout {
                id: boxCircuit

                anchors.fill: parent

                Repeater {
                    model: circuits

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
                                text: modelData.name
                            }

                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Image {
                                anchors.margins: 20
                                anchors.fill: parent
                                fillMode: Image.PreserveAspectFit
                                source: modelData.image
                            }

                        }

                    }

                }

            }

        }

    }

}
