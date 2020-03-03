import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    radius: 8
    anchors.centerIn: parent
    FontLoader {id:blackops; source: "../lib/blops.ttf"}
    property var btnText
    property var btnColor
    property var selected

    color: root.selected ? root.btnColor : "#333"

    Text {
        anchors.centerIn: parent
        color: "lightgray"
        text: root.btnText
        font.pointSize: 21
        font.family: blackops.name;
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
