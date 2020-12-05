import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property var btnText
    property var btnColor
    property var selected

    radius: 8
    anchors.centerIn: parent
    color: root.selected ? root.btnColor : "#333"

    Text {
        anchors.centerIn: parent
        color: "lightgray"
        text: root.btnText
        font: Style.sans.p
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

}
