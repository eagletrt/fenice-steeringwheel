import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int value
    property string unit
    property font valueFont: Style.mono.h1
    property font unitFont: Style.sans.p

    anchors.fill: parent

    RowLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        Item {
            Layout.fillWidth: true
        }

        Text {
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            text: root.value
            font: root.valueFont
            color: Style.text
            horizontalAlignment: Text.right
        }

        Text {
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            text: root.unit
            font: root.unitFont
            color: Style.text
        }

        Item {
            Layout.fillWidth: true
        }

    }

}
