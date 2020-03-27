import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    radius: 8
    anchors.centerIn: parent
    property var btnText
    property var btnColor
    property var selected

    color: root.selected ? root.btnColor : "#333"

    Text {
        anchors.centerIn: parent
        color: "lightgray"
        text: root.btnText
        font.pointSize: 10
        font.family: labelFont.name;
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
