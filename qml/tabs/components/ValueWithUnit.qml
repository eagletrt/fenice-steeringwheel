import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int value
    property string unit
    property font valueFont: Style.mono.h1
    property font unitFont: Style.sans.p

    width: main.width
    height: main.height

    Text {
        id: main
        text: root.value
        font: root.valueFont
        color: Style.text

        horizontalAlignment: Text.right
    }

    Text {
        id: other
        anchors.left: main.right
        anchors.leftMargin: 4
        anchors.verticalCenter: main.verticalCenter

        text: root.unit
        font: root.unitFont
        color: Style.text
    }
}
