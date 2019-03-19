import QtQuick 2.7

Rectangle {
    id: root
    height: 80
    property string text;
    color: "transparent"

    Text {
        anchors.fill: parent
        anchors.verticalCenter: root.verticalCenter
        id: statusText
        text: root.text
        padding: 5
        color: "lightgray"
    }
}
