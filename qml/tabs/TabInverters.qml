import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: status

    padding: 20

    contentItem: ColumnLayout {
        spacing: 10

        Text {
            text: "Tab Inverters"
            font: Style.mono.h2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: Style.text
        }

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
                subtitle: Car.inverters.left_motor_temp.toFixed(3)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "MOTOR TEMP INV R"
                subtitle: Car.inverters.right_motor_temp.toFixed(3)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "TEMP INV L"
                subtitle: Car.inverters.left_inverter_temp.toFixed(3)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "TEMP INV R"
                subtitle: Car.inverters.right_inverter_temp.toFixed(3)
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
                subtitle: "0x" + Car.inverters.left_status.toString(16)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "STATUS INV R"
                subtitle: "0x" + Car.inverters.right_status.toString(16)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "ERRORS INV L"
                subtitle: "0x" + Car.inverters.left_errors.toString(16)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "ERRORS INV R"
                subtitle: "0x" + Car.inverters.right_errors.toString(16)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "IO INFO INV L"
                subtitle: "0x" + Car.inverters.left_io_info.toString(16)
            }

            StatusBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                title: "IO INFO INV R"
                subtitle: "0x" + Car.inverters.right_io_info.toString(16)
            }

        }

    }

}
