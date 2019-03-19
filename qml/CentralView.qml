import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "transparent"

    GridLayout {
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        Layout.margins: 1

        StatusLED {
            id: statusleds

            height: 40
            Layout.fillWidth: true
        }

        SpeedGauge {
            id: speedgauge
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: parent.width
        }

        Presets {
            height: 20
            width: 365
        }
    }
}
