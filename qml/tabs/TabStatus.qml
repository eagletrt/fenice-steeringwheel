import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: status

    property var possibleStates: ['OK', 'NO', 'DEFAULT', 'OUTDATED']
    property var sensors: ["InvRight", "InvLeft", "STMFront", "STMCentral", "STMPedals", "STMRear", "BMS HV", "BMS LV"]

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
                model: sensors

                delegate: Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    StatusCard {
                        name: modelData
                        state: possibleStates[Math.floor(Math.random() * possibleStates.length)] // modelData[1]
                    }

                }

            }

        }

    }

}
