import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: status

    property var possibleStates: ['NORMAL', 'ERROR', 'DEFAULT', 'OUTDATED']
    property var sensors: ["Steering", "Telemetry", "Inverters", "DAS", "BMS HV", "BMS LV"]
    property var sensorInterfaces: []

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

            StatusBox {
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                Layout.columnSpan: 3

                title: 'Steering'
                state: "NORMAL"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "Inverter L"
                state: Car.inverters.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "TELEMETRY"
                state: Car.telemetry.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "INVERTER R"
                state: Car.inverters.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "BMS LV"
                state: Car.lv.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "DAS"
                state: Car.das.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "BMS HV"
                state: Car.hv.valid ? "NORMAL" : "ERROR"
            }
        }
    }
}
