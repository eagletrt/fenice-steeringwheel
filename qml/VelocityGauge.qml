import QtQuick 2.7

Rectangle {
    width: 180
    height: 180
    color: "transparent"
    anchors.centerIn: parent

    //property int value: Math.sqrt(acceleratore.width)*6
    property int value: 0

    Text {
        text: parent.value
        anchors.centerIn: parent
        color: "lightgray"
        font.family: labelFont.name;
        font.pointSize: 140
    }
}
