import QtQuick 2.7

Rectangle {
    id: root

    property string text

    height: 80
    color: "transparent"

    Text {
        id: statusText

        anchors.fill: parent
        anchors.verticalCenter: root.verticalCenter
        font: Style.sans.p
        text: root.text
        padding: 5
        color: "lightgray"
    }

}
