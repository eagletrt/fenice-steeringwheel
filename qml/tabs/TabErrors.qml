import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Control {
    id: tabErrors

    readonly property int binaryNLength: 32
    property bool hvValid: Car.hv.valid
    property bool lvValid: Car.lv.valid
    property bool dasValid: Car.das.valid

    property bool hvErrors: Car.hv.errors
    property bool lvErrors: Car.lv.errors
    property bool dasErrors: Car.das.errors
    property bool hvFeedbacks: Car.hv.feedbacks
    
    property var errors: {
        "HvErr_DEFAULT": [getError(1, hvErrors), hvValid],
        "HvErr_CELL_LOW_VOLT": [getError(2, hvErrors), hvValid],
        "HvErr_CELL_UNDER_VOLT": [getError(3, hvErrors), hvValid],
        "HvErr_CELL_OVER_VOLT": [getError(4, hvErrors), hvValid],
        "HvErr_CELL_HIGH_TEMP": [getError(5, hvErrors), hvValid],
        "HvErr_CELL_OVER_TEMP": [getError(6, hvErrors), hvValid],
        "HvErr_OVER_CURRENT": [getError(7, hvErrors), hvValid],
        "HvErr_CAN": [getError(8, hvErrors), hvValid],
        "HvErr_INT_VOLT_MISMATCH": [getError(9, hvErrors), hvValid],
        "HvErr_CELLBOARD_COMM": [getError(10, hvErrors), hvValid],
        "HvErr_CELLBOARD_INTERNAL": [getError(11, hvErrors), hvValid],
        "HvErr_FEEDBACK": [getError(12, hvErrors), hvValid],
        "HvErr_FEEDBACK_CIRCUITRY": [getError(13, hvErrors), hvValid],
        "HvErr_EEPROM_COMM": [getError(14, hvErrors), hvValid],
        "HvErr_EEPROM_WRITE": [getError(15, hvErrors), hvValid],
        "DasErr_DEFAULT": [getError(1, dasErrors), dasValid],
        "DasErr_PEDAL_ADC": [getError(2, dasErrors), dasValid],
        "DasErr_PEDAL_IMPLAUSIBILITY": [getError(3, dasErrors), dasValid],
        "DasErr_IMU_TOUT": [getError(4, dasErrors), dasValid],
        "DasErr_IRTS_TOUT": [getError(5, dasErrors), dasValid],
        "DasErr_TS_TOUT": [getError(6, dasErrors), dasValid],
        "DasErr_INVL_TOUT": [getError(7, dasErrors), dasValid],
        "DasErr_INVR_TOUT": [getError(8, dasErrors), dasValid],
        "DasErr_STEER_TOUT": [getError(9, dasErrors), dasValid],
        "DasErr_FSM": [getError(10, dasErrors), dasValid],
        "HvFB_DEFAULT": [getError(1, hvFeedbacks), hvValid],
        "HvFB_FB_TSAL_GREEN_FAULT": [getError(2, hvFeedbacks), hvValid],
        "HvFB_FB_IMD_LATCHED": [getError(3, hvFeedbacks), hvValid],
        "HvFB_FB_TSAL_GREEN_FAULT_LATCHED": [getError(4, hvFeedbacks), hvValid],
        "HvFB_FB_BMS_LATCHED": [getError(5, hvFeedbacks), hvValid],
        "HvFB_FB_EXT_LATCHED": [getError(6, hvFeedbacks), hvValid],
        "HvFB_FB_TSAL_GREEN": [getError(7, hvFeedbacks), hvValid],
        "HvFB_FB_TS_OVER_60V_STATUS": [getError(8, hvFeedbacks), hvValid],
        "HvFB_FB_AIRN_STATUS": [getError(9, hvFeedbacks), hvValid],
        "HvFB_FB_AIRP_STATUS": [getError(10, hvFeedbacks), hvValid],
        "HvFB_FB_AIRP_GATE": [getError(11, hvFeedbacks), hvValid],
        "HvFB_FB_AIRN_GATE": [getError(12, hvFeedbacks), hvValid],
        "HvFB_FB_PRECHARGE_STATUS": [getError(13, hvFeedbacks), hvValid],
        "HvFB_FB_TSP_OVER_60V_STATUS": [getError(14, hvFeedbacks), hvValid],
        "HvFB_FB_CHECK_MUX": [getError(15, hvFeedbacks), hvValid],
        "HvFB_FB_SD_IN": [getError(16, hvFeedbacks), hvValid],
        "HvFB_FB_SD_OUT": [getError(17, hvFeedbacks), hvValid],
        "HvFB_FB_RELAY_SD": [getError(18, hvFeedbacks), hvValid],
        "HvFB_FB_IMD_FAULT": [getError(19, hvFeedbacks), hvValid],
        "HvFB_FB_SD_END": [getError(20, hvFeedbacks), hvValid],
        "LvErr_DEFAULT": [getError(1, lvErrors), lvValid],
        "LvErr_CELL_UNDERVOLT": [getError(2, lvErrors), lvValid],
        "LvErr_CELL_OVERVOLT": [getError(3, lvErrors), lvValid],
        "LvErr_OPEN_WIRE": [getError(4, lvErrors), lvValid],
        "LvErr_CAN": [getError(5, lvErrors), lvValid],
        "LvErr_SPI": [getError(6, lvErrors), lvValid],
        "LvErr_OVER_CURRENT": [getError(7, lvErrors), lvValid],
        "LvErr_DCDC12_UNDER_TEMP": [getError(8, lvErrors), lvValid],
        "LvErr_DCDC12_OVER_TEMP": [getError(9, lvErrors), lvValid],
        "LvErr_DCDC24_UNDER_TEMP": [getError(10, lvErrors), lvValid],
        "LvErr_DCDC24_OVER_TEMP": [getError(11, lvErrors), lvValid],
        "LvErr_CELL_UNDER_TEMP": [getError(12, lvErrors), lvValid],
        "LvErr_CELL_OVER_TEMP": [getError(13, lvErrors), lvValid],
        "LvErr_RELAY": [getError(14, lvErrors), lvValid],
        "LvErr_LTC6810": [getError(15, lvErrors), lvValid],
        "LvErr_VOLTS_NOT_READY": [getError(16, lvErrors), lvValid],
        "LvErr_MCP23017": [getError(17, lvErrors), lvValid],
        "LvErr_RADIATOR": [getError(18, lvErrors), lvValid],
        "LvErr_FAN": [getError(19, lvErrors), lvValid],
        "LvErr_PUMP": [getError(20, lvErrors), lvValid],
        "LvErr_ADC_INIT": [getError(21, lvErrors), lvValid],
        "LvErr_DCDC12": [getError(22, lvErrors), lvValid],
        "LvErr_DCDC24": [getError(23, lvErrors), lvValid]
    }

    function getError(index, centralUnit) {
        return (centralUnit >>> 0).toString(2).padStart(binaryNLength, '0').charAt(binaryNLength - 1 * index);
    }

    padding: 20

    contentItem: GridLayout {
        columns: 5
        columnSpacing: 5
        rows: 18
        flow: GridLayout.TopToBottom

        Repeater {
            model: Object.entries(errors)

            ErrorEntry {
                errorText: modelData[0]
                error: modelData[1][0]
                valid: modelData[1][1]
            }

        }

    }

}
