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
            text: "General Debug Tab"
            font: Style.mono.h2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: Style.text
        }

        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            rows: 3
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            ValueWithUnitAndLabel {
                Layout.fillHeight: true
                Layout.fillWidth: true
                valid: true
                value: Car.steering.sc_values[Car.steering.slip_control_index] * 10
                unit: "%"
                label: "SLIP CONTROL"
            }

            ValueWithUnitAndLabel {
                Layout.fillHeight: true
                Layout.fillWidth: true
                valid: true
                value: Car.steering.tv_values[Car.steering.torque_vectoring_index] * 10
                unit: "%"
                label: "TORQUE VECTORING"
            }

            ValueWithUnitAndLabel {
                Layout.fillHeight: true
                Layout.fillWidth: true
                valid: true
                value: Car.steering.pm_values[Car.steering.power_map_index] * 10
                unit: "%"
                label: "MAX POWER"
            }

            ValueWithUnitAndLabel {
                Layout.fillHeight: true
                Layout.fillWidth: true
                valid: true
                value: [-1, 0, 25, 50, 75, 100][Car.steering.pumps_speed]
                unit: "%"
                label: "PUMP SPEED"
            }

            ValueWithUnitAndLabel {
                Layout.fillHeight: true
                Layout.fillWidth: true
                valid: true
                value: [-1, 0, 25, 50, 75, 100][Car.steering.radiators_speed]
                unit: "%"
                label: "RADIATOR SPEED"
            }

        }

    }

}
