import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Control {
    id: tabErrors

    readonly property var binaryNLength: 32
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
        "HvErrors_INT_VOLTAGE_MISMATCH": getError(9, Car.hv.errors),
        "HvErrors_CELLBOARD_COMM": getError(10, Car.hv.errors),
        "HvErrors_CELLBOARD_INTERNAL": getError(11, Car.hv.errors),
        "HvErrors_FEEDBACK": getError(12, Car.hv.errors),
        "HvErrors_FEEDBACK_CIRCUITRY": getError(13, Car.hv.errors),
        "HvErrors_EEPROM_COMM": getError(14, Car.hv.errors),
        "HvErrors_EEPROM_WRITE": getError(15, Car.hv.errors),
        "DasErrors_DEFAULT": getError(1, Car.das.errors),
        "DasErrors_PEDAL_ADC": getError(2, Car.das.errors),
        "DasErrors_PEDAL_IMPLAUSIBILITY": getError(3, Car.das.errors),
        "DasErrors_IMU_TOUT": getError(4, Car.das.errors),
        "DasErrors_IRTS_TOUT": getError(5, Car.das.errors),
        "DasErrors_TS_TOUT": getError(6, Car.das.errors),
        "DasErrors_INVL_TOUT": getError(7, Car.das.errors),
        "DasErrors_INVR_TOUT": getError(8, Car.das.errors),
        "DasErrors_STEER_TOUT": getError(9, Car.das.errors),
        "DasErrors_FSM": getError(10, Car.das.errors),
        "HvFeedbacks_DEFAULT": getError(1, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_TSAL_GREEN_FAULT": getError(2, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_IMD_LATCHED": getError(3, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_TSAL_GREEN_FAULT_LATCHED": getError(4, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_BMS_LATCHED": getError(5, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_EXT_LATCHED": getError(6, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_TSAL_GREEN": getError(7, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_TS_OVER_60V_STATUS": getError(8, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_AIRN_STATUS": getError(9, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_AIRP_STATUS": getError(10, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_AIRP_GATE": getError(11, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_AIRN_GATE": getError(12, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_PRECHARGE_STATUS": getError(13, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_TSP_OVER_60V_STATUS": getError(14, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_CHECK_MUX": getError(15, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_SD_IN": getError(16, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_SD_OUT": getError(17, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_RELAY_SD": getError(18, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_IMD_FAULT": getError(19, Car.hv.feedbacks),
        "HvFeedbacks_FEEDBACK_SD_END": getError(20, Car.hv.feedbacks),
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
