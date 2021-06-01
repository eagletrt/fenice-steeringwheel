import QtQuick 2.7

Rectangle {
    // property int value: Math.sqrt(acceleratore.width)*6
    property int value: 0

    width: 180
    height: 180
    color: "transparent"
    anchors.centerIn: parent

    Text {
        text: parent.value
        anchors.centerIn: parent
        color: "lightgray"
        font: Style.sans.h1
    }

}
