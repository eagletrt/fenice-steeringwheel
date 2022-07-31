import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Control {
    id: tabErrors

    readonly property var binaryNLength: 32
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
        "HvFB_DEFAULT": getError(1, Car.hv.feedbacks),
        "HvFB_FB_TSAL_GREEN_FAULT": getError(2, Car.hv.feedbacks),
        "HvFB_FB_IMD_LATCHED": getError(3, Car.hv.feedbacks),
        "HvFB_FB_TSAL_GREEN_FAULT_LATCHED": getError(4, Car.hv.feedbacks),
        "HvFB_FB_BMS_LATCHED": getError(5, Car.hv.feedbacks),
        "HvFB_FB_EXT_LATCHED": getError(6, Car.hv.feedbacks),
        "HvFB_FB_TSAL_GREEN": getError(7, Car.hv.feedbacks),
        "HvFB_FB_TS_OVER_60V_STATUS": getError(8, Car.hv.feedbacks),
        "HvFB_FB_AIRN_STATUS": getError(9, Car.hv.feedbacks),
        "HvFB_FB_AIRP_STATUS": getError(10, Car.hv.feedbacks),
        "HvFB_FB_AIRP_GATE": getError(11, Car.hv.feedbacks),
        "HvFB_FB_AIRN_GATE": getError(12, Car.hv.feedbacks),
        "HvFB_FB_PRECHARGE_STATUS": getError(13, Car.hv.feedbacks),
        "HvFB_FB_TSP_OVER_60V_STATUS": getError(14, Car.hv.feedbacks),
        "HvFB_FB_CHECK_MUX": getError(15, Car.hv.feedbacks),
        "HvFB_FB_SD_IN": getError(16, Car.hv.feedbacks),
        "HvFB_FB_SD_OUT": getError(17, Car.hv.feedbacks),
        "HvFB_FB_RELAY_SD": getError(18, Car.hv.feedbacks),
        "HvFB_FB_IMD_FAULT": getError(19, Car.hv.feedbacks),
        "HvFB_FB_SD_END": getError(20, Car.hv.feedbacks)
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
            model: Object.entries(errors)

            ErrorEntry {
                errorText: modelData[0]
                error: modelData[1]
            }

        }

    }

}
