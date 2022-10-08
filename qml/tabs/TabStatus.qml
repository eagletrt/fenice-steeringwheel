import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: status

    padding: 20

    contentItem: GridLayout {

        GridLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true

            columns: 2
            rows: 4
            columnSpacing: 10
            rowSpacing: 5
            flow: GridLayout.TopToBottom

            StatusBox {
                width: 300
                height: 80
                title: "STEERING IP ADDRESS"
                subtitle: Car.steering.ip_addr
            }

            StatusBox {
                width: 300
                height: 80
                title: "BUILD DATE TIME"
                subtitle: Car.steering.build_date_time
            }

            StatusBox {
                width: 300
                height: 80
                title: "CANLIB BUILD HASH"
                subtitle: Car.steering.canlib_build_hash.toString(16)
            }

            StatusBox {
                width: 300
                height: 80
                title: "CANLIB BUILD DATETIME"
                subtitle: Car.steering.canlib_build_time
            }

            StatusBox {
                width: 300
                height: 80
                title: "DAS CANLIB DATETIME"
                subtitle: Car.das.canlib_build_time
            }

            StatusBox {
                width: 300
                height: 80
                title: "HV CANLIB DATETIME"
                subtitle: Car.hv.canlib_build_time
            }

            StatusBox {
                width: 300
                height: 80
                title: "LV CANLIB DATETIME"
                subtitle: Car.lv.canlib_build_time
            }

            StatusBox {
                width: 300
                height: 80
                title: "TELEMETRY CANLIB DATETIME"
                subtitle: Car.telemetry.canlib_build_time
            }

        }

    }

}
