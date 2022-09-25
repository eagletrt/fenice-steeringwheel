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
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "MOTOR TEMP INV L"
                subtitle: Car.inverters.left_motor_temp
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "MOTOR TEMP INV R"
                subtitle: Car.inverters.right_motor_temp
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "TEMP INV L"
                subtitle: Car.inverters.left_inverter_temp
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "TEMP INV R"
                subtitle: Car.inverters.right_inverter_temp
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "SPEED INV L"
                subtitle: Car.inverters.left_speed
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "SPEED INV R"
                subtitle: Car.inverters.right_speed
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "STATUS INV L"
                subtitle: Car.inverters.left_status
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "STATUS INV R"
                subtitle: Car.inverters.right_status
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "ERRORS INV L"
                subtitle: Car.inverters.left_errors
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "ERRORS INV R"
                subtitle: Car.inverters.right_errors
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "IO INFO INV L"
                subtitle: Car.inverters.left_io_info
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "IO INFO INV R"
                subtitle: Car.inverters.right_io_info
            }

        }

    }

}
