import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Control {
    id: tabErrors

    readonly property var binaryNLength: 32
    property var errors: {
        "HvErr_DEFAULT":                     getError(1, Car.hv.errors),
        "HvErr_CELL_LOW_VOLT":            getError(2, Car.hv.errors),
        "HvErr_CELL_UNDER_VOLT":          getError(3, Car.hv.errors),
        "HvErr_CELL_OVER_VOLT":           getError(4, Car.hv.errors),
        "HvErr_CELL_HIGH_TEMP":       getError(5, Car.hv.errors),
        "HvErr_CELL_OVER_TEMP":       getError(6, Car.hv.errors),
        "HvErr_OVER_CURRENT":                getError(7, Car.hv.errors),
        "HvErr_CAN":                         getError(8, Car.hv.errors),
        "HvErr_INT_VOLT_MISMATCH":        getError(9, Car.hv.errors),
        "HvErr_CELLBOARD_COMM":              getError(10, Car.hv.errors),
        "HvErr_CELLBOARD_INTERNAL":          getError(11, Car.hv.errors),
        "HvErr_FEEDBACK":                    getError(12, Car.hv.errors),
        "HvErr_FEEDBACK_CIRCUITRY":          getError(13, Car.hv.errors),
        "HvErr_EEPROM_COMM":                 getError(14, Car.hv.errors),
        "HvErr_EEPROM_WRITE":                getError(15, Car.hv.errors),

        "DasErr_DEFAULT":                    getError(1, Car.das.errors),
        "DasErr_PEDAL_ADC":                  getError(2, Car.das.errors),
        "DasErr_PEDAL_IMPLAUSIBILITY":       getError(3, Car.das.errors),
        "DasErr_IMU_TOUT":                   getError(4, Car.das.errors),
        "DasErr_IRTS_TOUT":                  getError(5, Car.das.errors),
        "DasErr_TS_TOUT":                    getError(6, Car.das.errors),
        "DasErr_INVL_TOUT":                  getError(7, Car.das.errors),
        "DasErr_INVR_TOUT":                  getError(8, Car.das.errors),
        "DasErr_STEER_TOUT":                 getError(9, Car.das.errors),
        "DasErr_FSM":                        getError(10, Car.das.errors),

        "HvFB_DEFAULT":                      getError(1, Car.hv.feedbacks),
        "HvFB_FB_TSAL_GREEN_FAULT":          getError(2, Car.hv.feedbacks),
        "HvFB_FB_IMD_LATCHED":               getError(3, Car.hv.feedbacks),
        "HvFB_FB_TSAL_GREEN_FAULT_LATCHED":  getError(4, Car.hv.feedbacks),
        "HvFB_FB_BMS_LATCHED":               getError(5, Car.hv.feedbacks),
        "HvFB_FB_EXT_LATCHED":               getError(6, Car.hv.feedbacks),
        "HvFB_FB_TSAL_GREEN":                getError(7, Car.hv.feedbacks),
        "HvFB_FB_TS_OVER_60V_STATUS":        getError(8, Car.hv.feedbacks),
        "HvFB_FB_AIRN_STATUS":               getError(9, Car.hv.feedbacks),
        "HvFB_FB_AIRP_STATUS":               getError(10, Car.hv.feedbacks),
        "HvFB_FB_AIRP_GATE":                 getError(11, Car.hv.feedbacks),
        "HvFB_FB_AIRN_GATE":                 getError(12, Car.hv.feedbacks),
        "HvFB_FB_PRECHARGE_STATUS":          getError(13, Car.hv.feedbacks),
        "HvFB_FB_TSP_OVER_60V_STATUS":       getError(14, Car.hv.feedbacks),
        "HvFB_FB_CHECK_MUX":                 getError(15, Car.hv.feedbacks),
        "HvFB_FB_SD_IN":                     getError(16, Car.hv.feedbacks),
        "HvFB_FB_SD_OUT":                    getError(17, Car.hv.feedbacks),
        "HvFB_FB_RELAY_SD":                  getError(18, Car.hv.feedbacks),
        "HvFB_FB_IMD_FAULT":                 getError(19, Car.hv.feedbacks),
        "HvFB_FB_SD_END":                    getError(20, Car.hv.feedbacks),

        "LvErr_DEFAULT":                     getError(1, Car.lv.errors),
        "LvErr_CELL_UNDERVOLT":           getError(2, Car.lv.errors),
        "LvErr_CELL_OVERVOLT":            getError(3, Car.lv.errors),
        "LvErr_OPEN_WIRE":                   getError(4, Car.lv.errors),
        "LvErr_CAN":                         getError(5, Car.lv.errors),
        "LvErr_SPI":                         getError(6, Car.lv.errors),
        "LvErr_OVER_CURRENT":                getError(7, Car.lv.errors),
        "LvErr_DCDC12_UNDER_TEMP":    getError(8, Car.lv.errors),
        "LvErr_DCDC12_OVER_TEMP":     getError(9, Car.lv.errors),
        "LvErr_DCDC24_UNDER_TEMP":    getError(10, Car.lv.errors),
        "LvErr_DCDC24_OVER_TEMP":     getError(11, Car.lv.errors),
        "LvErr_CELL_UNDER_TEMP":      getError(12, Car.lv.errors),
        "LvErr_CELL_OVER_TEMP":       getError(13, Car.lv.errors),
        "LvErr_RELAY":                       getError(14, Car.lv.errors),
        "LvErr_LTC6810":                     getError(15, Car.lv.errors),
        "LvErr_VOLTS_NOT_READY":          getError(16, Car.lv.errors),
        "LvErr_MCP23017":                    getError(17, Car.lv.errors),
        "LvErr_RADIATOR":                    getError(18, Car.lv.errors),
        "LvErr_FAN":                         getError(19, Car.lv.errors),
        "LvErr_PUMP":                        getError(20, Car.lv.errors),
        "LvErr_ADC_INIT":                    getError(21, Car.lv.errors),
        "LvErr_DCDC12":                      getError(22, Car.lv.errors),
        "LvErr_DCDC24":                      getError(23, Car.lv.errors)
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
                error: modelData[1]
            }

        }

    }

}
