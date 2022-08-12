// THIS FILE WAS AUTOMATICALLY GENERATED
import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Control {
    readonly property int binaryNLength: 32
    readonly property int nErrors: 22
    property int centralUnit: Car.lv.errors
    property int cell_undervolt: getError(1)
    property int cell_overvolt: getError(2)
    property int open_wire: getError(3)
    property int can: getError(4)
    property int spi: getError(5)
    property int over_current: getError(6)
    property int dcdc12_under_temp: getError(7)
    property int dcdc12_over_temp: getError(8)
    property int dcdc24_under_temp: getError(9)
    property int dcdc24_over_temp: getError(10)
    property int cell_under_temp: getError(11)
    property int cell_over_temp: getError(12)
    property int relay: getError(13)
    property int ltc6810: getError(14)
    property int volts_not_ready: getError(15)
    property int mcp23017: getError(16)
    property int radiator: getError(17)
    property int fan: getError(18)
    property int pump: getError(19)
    property int adc_init: getError(20)
    property int dcdc12: getError(21)
    property int dcdc24: getError(22)

    function getError(index) {
        return (centralUnit >>> 0).toString(2).padStart(binaryNLength, '0').slice(0 - index).charAt(0);
    }

    padding: 20

    contentItem: ColumnLayout {
        anchors.fill: parent

        Text {
            text: "LvErrors"
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
                id: cell_undervolt_id

                errorText: "CELL_UNDERVOLT"
                error: cell_undervolt
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cell_overvolt_id

                errorText: "CELL_OVERVOLT"
                error: cell_overvolt
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: open_wire_id

                errorText: "OPEN_WIRE"
                error: open_wire
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: can_id

                errorText: "CAN"
                error: can
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: spi_id

                errorText: "SPI"
                error: spi
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: over_current_id

                errorText: "OVER_CURRENT"
                error: over_current
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: dcdc12_under_temp_id

                errorText: "DCDC12_UNDER_TEMP"
                error: dcdc12_under_temp
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: dcdc12_over_temp_id

                errorText: "DCDC12_OVER_TEMP"
                error: dcdc12_over_temp
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: dcdc24_under_temp_id

                errorText: "DCDC24_UNDER_TEMP"
                error: dcdc24_under_temp
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: dcdc24_over_temp_id

                errorText: "DCDC24_OVER_TEMP"
                error: dcdc24_over_temp
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cell_under_temp_id

                errorText: "CELL_UNDER_TEMP"
                error: cell_under_temp
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: cell_over_temp_id

                errorText: "CELL_OVER_TEMP"
                error: cell_over_temp
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: relay_id

                errorText: "RELAY"
                error: relay
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: ltc6810_id

                errorText: "LTC6810"
                error: ltc6810
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: volts_not_ready_id

                errorText: "VOLTS_NOT_READY"
                error: volts_not_ready
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: mcp23017_id

                errorText: "MCP23017"
                error: mcp23017
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: radiator_id

                errorText: "RADIATOR"
                error: radiator
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: fan_id

                errorText: "FAN"
                error: fan
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: pump_id

                errorText: "PUMP"
                error: pump
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: adc_init_id

                errorText: "ADC_INIT"
                error: adc_init
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: dcdc12_id

                errorText: "DCDC12"
                error: dcdc12
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: dcdc24_id

                errorText: "DCDC24"
                error: dcdc24
                valid: Car.lv.valid
                cols: errorGrid.columns
            }

        }

    }

}
