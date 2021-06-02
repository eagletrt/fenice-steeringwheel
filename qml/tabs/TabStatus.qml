import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: status

    //    property var canstatus: CarStatus.CANStatus
    property var ledStates: ['OK', 'NO', 'DEFAULT', 'OUTDATED']
    property var canLeds: [["InvRight", 'CAN_DEFAULT'], ["InvLeft", 'CAN_DEFAULT'], ["STMFront", 'CAN_DEFAULT'], ["STMCentral", 'CAN_DEFAULT'], ["STMPedals", 'CAN_DEFAULT'], ["STMRear", 'CAN_DEFAULT'], ["BMS HV", 'CAN_DEFAULT'], ["BMS LV", 'CAN_DEFAULT']]

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

            Repeater {
                model: canLeds

                delegate: Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    StatusCard {
                        name: modelData[0]
                        state: ledStates[Math.floor(Math.random() * ledStates.length)] // modelData[1]
                    }

                }

            }

        }

    }

}
