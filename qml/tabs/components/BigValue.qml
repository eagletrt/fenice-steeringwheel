import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    property int value
    property string unit

    anchors.fill: parent
    anchors.centerIn: parent

    RowLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        Item {
            Layout.fillWidth: true
        }

        Text {
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            text: String(value).padStart(3, " ")
            color: Style.text
            font: Style.mono.verybig
            horizontalAlignment: Text.right
        }

        Text {
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            text: unit
            color: Style.text
            font: Style.sans.h3
        }

        Item {
            Layout.fillWidth: true
        }

    }

}