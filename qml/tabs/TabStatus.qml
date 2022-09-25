import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: status

    padding: 20

    contentItem: ColumnLayout {
        spacing: 10

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter || Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true

            StatusBox {
                width: 400
                height: 100
                title: "Steering"
                state: "NORMAL"
                subtitle: "IP: " + Car.steering.ip_addr
            }

            StatusBox {
                width: 400
                height: 100
                title: "BUILD DATE"
                state: Car.inverters.valid ? "NORMAL" : "ERROR"
                subtitle: Car.steering.build_date_time
            }

            StatusBox {
                width: 400
                height: 100
                title: "CANLIB BUILD HASH"
                state: Car.inverters.valid ? "NORMAL" : "ERROR"
                subtitle: Car.steering.canlib_build_hash.toString(16)
            }

        }

    }

}
