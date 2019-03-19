import QtQuick 2.7

Rectangle {
    FontLoader {id:blackops; source: "../lib/blops.ttf"}
    id: root
    height: 80
    property string text;
    color: "transparent"

    Text {
        anchors.fill: parent
        anchors.verticalCenter: root.verticalCenter
        font.family: blackops.name;
        id: statusText
        text: root.text
        padding: 5
        color: "lightgray"
    }
}
