import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: status

    property var possibleStates: ['NORMAL', 'ERROR', 'DEFAULT', 'OUTDATED']
    property var sensors: ["Inv Right", "Telemetry", "Inv Left", "DAS", "PCU", "BMS HV", "Steering", "BMS LV"]

    padding: 20

    contentItem: ColumnLayout {
        spacing: 10

        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            rows: 5
            columns: 3
            rowSpacing: 10
            columnSpacing: 10

            Repeater {
                model: sensors.slice(0, 4)

                delegate: Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    StatusBox {
                        title: modelData
                        state: possibleStates[Math.floor(Math.random() * possibleStates.length)] // modelData[1]
                    }

                }

            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:///qml/img/eagle.png"
                }

            }

            Repeater {
                model: sensors.slice(4, 8)

                delegate: Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    StatusBox {
                        title: modelData
                        state: possibleStates[Math.floor(Math.random() * possibleStates.length)] // modelData[1]
                    }

                }

            }

        }

    }

}
