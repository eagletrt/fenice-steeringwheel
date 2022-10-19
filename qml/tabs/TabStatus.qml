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
            rows: 3
            columns: 3
            rowSpacing: 10
            columnSpacing: 10


            StatusBox {
                Layout.fillWidth: true
                Layout.preferredHeight: 120
                Layout.columnSpan: 3
                state: "NORMAL"
                title: "STEERING IP ADDRESS"
                subtitle: Car.steering.ip_addr
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                state: "NORMAL"
                title: "STEERING CANLIB DATETIME"
                subtitle: Car.steering.canlib_build_time
            }            

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                state: "NORMAL"
                title: "BUILD DATE TIME"
                subtitle: Car.steering.build_date_time
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "TELEMETRY CANLIB DATETIME"
                subtitle: Car.telemetry.canlib_build_time
                state: Car.telemetry.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "LV CANLIB DATETIME"
                subtitle: Car.lv.canlib_build_time
                state: Car.lv.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "DAS CANLIB DATETIME"
                subtitle: Car.das.canlib_build_time
                state: Car.das.valid ? "NORMAL" : "ERROR"
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "HV CANLIB DATETIME"
                subtitle: Car.hv.canlib_build_time
                state: Car.hv.valid ? "NORMAL" : "ERROR"
            }

        }

    }

}
