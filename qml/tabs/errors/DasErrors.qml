// THIS FILE WAS AUTOMATICALLY GENERATED
import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Control {
    readonly property int binaryNLength: 32
    readonly property int nErrors: 9
    property int centralUnit: Car.das.errors
    property int pedal_adc: getError(1)
    property int pedal_implaus: getError(2)
    property int imu_tout: getError(3)
    property int irts_tout: getError(4)
    property int ts_tout: getError(5)
    property int invl_tout: getError(6)
    property int invr_tout: getError(7)
    property int steer_tout: getError(8)
    property int fsm: getError(9)

    function getError(index) {
        return (centralUnit >>> 0).toString(2).padStart(binaryNLength, '0').slice(0 - index).charAt(0);
    }

    padding: 20

    contentItem: ColumnLayout {
        anchors.fill: parent

        Text {
            text: "DasErrors"
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
                id: pedal_adc_id

                errorText: "PEDAL_ADC"
                error: pedal_adc
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: pedal_implaus_id

                errorText: "PEDAL_IMPLAUS"
                error: pedal_implaus
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: imu_tout_id

                errorText: "IMU_TOUT"
                error: imu_tout
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: irts_tout_id

                errorText: "IRTS_TOUT"
                error: irts_tout
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: ts_tout_id

                errorText: "TS_TOUT"
                error: ts_tout
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: invl_tout_id

                errorText: "INVL_TOUT"
                error: invl_tout
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: invr_tout_id

                errorText: "INVR_TOUT"
                error: invr_tout
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: steer_tout_id

                errorText: "STEER_TOUT"
                error: steer_tout
                valid: Car.das.valid
                cols: errorGrid.columns
            }

            ErrorEntry {
                id: fsm_id

                errorText: "FSM"
                error: fsm
                valid: Car.das.valid
                cols: errorGrid.columns
            }

        }

    }

}
