import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Control {
    id: tabErrors

    readonly property var binaryNLength: 20
    readonly property var errorTexts: ['HvErrors_DEFAULT', 'HvErrors_CELL_LOW_VOLTAGE', 'HvErrors_CELL_UNDER_VOLTAGE', 'HvErrors_CELL_OVER_VOLTAGE', 'HvErrors_CELL_HIGH_TEMPERATURE', 'HvErrors_CELL_OVER_TEMPERATURE', 'HvErrors_OVER_CURRENT', 'HvErrors_CAN', 'HvErrors_INT_VOLTAGE_MISMATCH', 'HvErrors_CELLBOARD_COMM', 'HvErrors_CELLBOARD_INTERNAL', 'HvErrors_FEEDBACK', 'HvErrors_FEEDBACK_CIRCUITRY', 'HvErrors_EEPROM_COMM', 'HvErrors_EEPROM_WRITE', 'DasErrors_DEFAULT', 'DasErrors_PEDAL_ADC', 'DasErrors_PEDAL_IMPLAUSIBILITY', 'DasErrors_IMU_TOUT', 'DasErrors_IRTS_TOUT', 'DasErrors_TS_TOUT', 'DasErrors_INVL_TOUT', 'DasErrors_INVR_TOUT', 'DasErrors_STEER_TOUT', 'DasErrors_FSM', 'HvFeedbacks_DEFAULT', 'HvFeedbacks_FEEDBACK_TSAL_GREEN_FAULT', 'HvFeedbacks_FEEDBACK_IMD_LATCHED', 'HvFeedbacks_FEEDBACK_TSAL_GREEN_FAULT_LATCHED', 'HvFeedbacks_FEEDBACK_BMS_LATCHED', 'HvFeedbacks_FEEDBACK_EXT_LATCHED', 'HvFeedbacks_FEEDBACK_TSAL_GREEN', 'HvFeedbacks_FEEDBACK_TS_OVER_60V_STATUS', 'HvFeedbacks_FEEDBACK_AIRN_STATUS', 'HvFeedbacks_FEEDBACK_AIRP_STATUS', 'HvFeedbacks_FEEDBACK_AIRP_GATE', 'HvFeedbacks_FEEDBACK_AIRN_GATE', 'HvFeedbacks_FEEDBACK_PRECHARGE_STATUS', 'HvFeedbacks_FEEDBACK_TSP_OVER_60V_STATUS', 'HvFeedbacks_FEEDBACK_CHECK_MUX', 'HvFeedbacks_FEEDBACK_SD_IN', 'HvFeedbacks_FEEDBACK_SD_OUT', 'HvFeedbacks_FEEDBACK_RELAY_SD', 'HvFeedbacks_FEEDBACK_IMD_FAULT', 'HvFeedbacks_FEEDBACK_SD_END']
    readonly property var nErrors: errorTexts.length
    property var errors: {
        "HvErrors_DEFAULT": getError(1, Car.hv.errors),
        "HvErrors_CELL_LOW_VOLTAGE": getError(2, Car.hv.errors),
        "HvErrors_CELL_UNDER_VOLTAGE": getError(3, Car.hv.errors),
        "HvErrors_CELL_OVER_VOLTAGE": getError(4, Car.hv.errors),
        "HvErrors_CELL_HIGH_TEMPERATURE": getError(5, Car.hv.errors),
        "HvErrors_CELL_OVER_TEMPERATURE": getError(6, Car.hv.errors),
        "HvErrors_OVER_CURRENT": getError(7, Car.hv.errors),
        "HvErrors_CAN": getError(8, Car.hv.errors),
        "HvErrors_INT_VOLTAGE_MISMATCH": 0,
        "HvErrors_CELLBOARD_COMM": 0,
        "HvErrors_CELLBOARD_INTERNAL": 1,
        "HvErrors_FEEDBACK": 0,
        "HvErrors_FEEDBACK_CIRCUITRY": 0,
        "HvErrors_EEPROM_COMM": 0,
        "HvErrors_EEPROM_WRITE": 0,
        "DasErrors_DEFAULT": 0,
        "DasErrors_PEDAL_ADC": 0,
        "DasErrors_PEDAL_IMPLAUSIBILITY": 0,
        "DasErrors_IMU_TOUT": 0,
        "DasErrors_IRTS_TOUT": 0,
        "DasErrors_TS_TOUT": 0,
        "DasErrors_INVL_TOUT": 0,
        "DasErrors_INVR_TOUT": 0,
        "DasErrors_STEER_TOUT": 0,
        "DasErrors_FSM": 0,
        "HvFeedbacks_DEFAULT": 0,
        "HvFeedbacks_FEEDBACK_TSAL_GREEN_FAULT": 0,
        "HvFeedbacks_FEEDBACK_IMD_LATCHED": 0,
        "HvFeedbacks_FEEDBACK_TSAL_GREEN_FAULT_LATCHED": 0,
        "HvFeedbacks_FEEDBACK_BMS_LATCHED": 0,
        "HvFeedbacks_FEEDBACK_EXT_LATCHED": 0,
        "HvFeedbacks_FEEDBACK_TSAL_GREEN": 0,
        "HvFeedbacks_FEEDBACK_TS_OVER_60V_STATUS": 0,
        "HvFeedbacks_FEEDBACK_AIRN_STATUS": 0,
        "HvFeedbacks_FEEDBACK_AIRP_STATUS": 0,
        "HvFeedbacks_FEEDBACK_AIRP_GATE": 0,
        "HvFeedbacks_FEEDBACK_AIRN_GATE": 0,
        "HvFeedbacks_FEEDBACK_PRECHARGE_STATUS": 0,
        "HvFeedbacks_FEEDBACK_TSP_OVER_60V_STATUS": 0,
        "HvFeedbacks_FEEDBACK_CHECK_MUX": 0,
        "HvFeedbacks_FEEDBACK_SD_IN": 0,
        "HvFeedbacks_FEEDBACK_SD_OUT": 0,
        "HvFeedbacks_FEEDBACK_RELAY_SD": 0,
        "HvFeedbacks_FEEDBACK_IMD_FAULT": 0,
        "HvFeedbacks_FEEDBACK_SD_END": 0
    }

    function getError(index, centralUnit) {
        return (centralUnit >>> 0).toString(2).padStart(binaryNLength, '0').charAt(binaryNLength - 1 * index);
    }

    padding: 20

    contentItem: GridLayout {
        columns: 5
        columnSpacing: 10
        rows: 15
        flow: GridLayout.TopToBottom

        Repeater {
            model: nErrors

            ErrorEntry {
                errorText: errorTexts[index]
                error: errors[errorTexts[index]]
            }

        }

    }

}
