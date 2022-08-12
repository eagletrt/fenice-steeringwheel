// THIS FILE WAS AUTOMATICALLY GENERATED
import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Control {
    readonly property int binaryNLength: 32
    readonly property int nErrors: 14
    property int centralUnit: Car.hv.errors
    property int cell_low_voltage: getError(1)
    property int cell_under_volt: getError(2)
    property int cell_over_volt: getError(3)
    property int cell_high_temp: getError(4)
    property int cell_over_temp: getError(5)
    property int over_current: getError(6)
    property int can: getError(7)
    property int int_voltage_mismatch: getError(8)
    property int cellboard_comm: getError(9)
    property int cellboard_internal: getError(10)
    property int feedback: getError(11)
    property int feedback_circuitry: getError(12)
    property int eeprom_comm: getError(13)
    property int eeprom_write: getError(14)

    function getError(index) {
        return (centralUnit >>> 0).toString(2).padStart(binaryNLength, '0').slice(0 - index).charAt(0);
    }

    padding: 20

    contentItem: ColumnLayout {
        anchors.fill: parent

        Text {
            text: "HvErrors"
            font: Style.mono.h2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: Style.text
        }

        GridLayout {
            id: errorGrid

            rows: 5
            columns: Math.ceil(nErrors / 5)
            flow: GridLayout.TopToBottom
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            ErrorEntry {
                id: cell_low_voltage_id

                errorText: "CELL_LOW_VOLTAGE"
                error: cell_low_voltage
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cell_under_volt_id

                errorText: "CELL_UNDER_VOLT"
                error: cell_under_volt
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cell_over_volt_id

                errorText: "CELL_OVER_VOLT"
                error: cell_over_volt
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cell_high_temp_id

                errorText: "CELL_HIGH_TEMP"
                error: cell_high_temp
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cell_over_temp_id

                errorText: "CELL_OVER_TEMP"
                error: cell_over_temp
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: over_current_id

                errorText: "OVER_CURRENT"
                error: over_current
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: can_id

                errorText: "CAN"
                error: can
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: int_voltage_mismatch_id

                errorText: "INT_VOLTAGE_MISMATCH"
                error: int_voltage_mismatch
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cellboard_comm_id

                errorText: "CELLBOARD_COMM"
                error: cellboard_comm
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cellboard_internal_id

                errorText: "CELLBOARD_INTERNAL"
                error: cellboard_internal
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: feedback_id

                errorText: "FEEDBACK"
                error: feedback
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: feedback_circuitry_id

                errorText: "FEEDBACK_CIRCUITRY"
                error: feedback_circuitry
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: eeprom_comm_id

                errorText: "EEPROM_COMM"
                error: eeprom_comm
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: eeprom_write_id

                errorText: "EEPROM_WRITE"
                error: eeprom_write
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

        }

    }

}
