// THIS FILE WAS AUTOMATICALLY GENERATED
import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Control {
    readonly property int binaryNLength: 32
    readonly property int nErrors: 19
    property int centralUnit: Car.hv.feedbacks
    property int tsal_green_fault: getError(1)
    property int imd_latched: getError(2)
    property int tsal_green_f_latched: getError(3)
    property int bms_latched: getError(4)
    property int ext_latched: getError(5)
    property int tsal_green: getError(6)
    property int ts_over_60v_status: getError(7)
    property int airn_status: getError(8)
    property int airp_status: getError(9)
    property int airp_gate: getError(10)
    property int airn_gate: getError(11)
    property int precharge_status: getError(12)
    property int tsp_over_60v_status: getError(13)
    property int check_mux: getError(14)
    property int sd_in: getError(15)
    property int sd_out: getError(16)
    property int relay_sd: getError(17)
    property int imd_fault: getError(18)
    property int sd_end: getError(19)

    function getError(index) {
        return (centralUnit >>> 0).toString(2).padStart(binaryNLength, '0').slice(0 - index).charAt(0);
    }

    padding: 20

    contentItem: ColumnLayout {
        anchors.fill: parent

        Text {
            text: "HvFeedbacks"
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
                id: tsal_green_fault_id

                errorText: "TSAL_GREEN_FAULT"
                error: tsal_green_fault
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: imd_latched_id

                errorText: "IMD_LATCHED"
                error: imd_latched
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: tsal_green_f_latched_id

                errorText: "TSAL_GREEN_F_LATCHED"
                error: tsal_green_f_latched
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: bms_latched_id

                errorText: "BMS_LATCHED"
                error: bms_latched
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: ext_latched_id

                errorText: "EXT_LATCHED"
                error: ext_latched
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: tsal_green_id

                errorText: "TSAL_GREEN"
                error: tsal_green
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: ts_over_60v_status_id

                errorText: "TS_OVER_60V_STATUS"
                error: ts_over_60v_status
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: airn_status_id

                errorText: "AIRN_STATUS"
                error: airn_status
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: airp_status_id

                errorText: "AIRP_STATUS"
                error: airp_status
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: airp_gate_id

                errorText: "AIRP_GATE"
                error: airp_gate
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: airn_gate_id

                errorText: "AIRN_GATE"
                error: airn_gate
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: precharge_status_id

                errorText: "PRECHARGE_STATUS"
                error: precharge_status
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: tsp_over_60v_status_id

                errorText: "TSP_OVER_60V_STATUS"
                error: tsp_over_60v_status
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: check_mux_id

                errorText: "CHECK_MUX"
                error: check_mux
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: sd_in_id

                errorText: "SD_IN"
                error: sd_in
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: sd_out_id

                errorText: "SD_OUT"
                error: sd_out
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: relay_sd_id

                errorText: "RELAY_SD"
                error: relay_sd
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: imd_fault_id

                errorText: "IMD_FAULT"
                error: imd_fault
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: sd_end_id

                errorText: "SD_END"
                error: sd_end
                valid: Car.hv.valid
                cols: errorGrid.columns
            }

        }

    }

}
