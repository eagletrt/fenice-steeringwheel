import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    color: "transparent"

    GridLayout {
        // Maps {
        //     height: 20
        //     width: 365
        // }

        anchors.fill: parent
        flow: GridLayout.TopToBottom
        Layout.margins: 1

        StatusLED {
            id: statusleds

            height: 80
            Layout.fillWidth: true
        }

        SpeedGauge {
            id: speedgauge

            Layout.fillHeight: true
            Layout.fillWidth: true
            width: parent.width
        }

    }

}