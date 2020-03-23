import QtQuick 2.0

Rectangle {
    id: root
    property var activeColor
    property var text

    anchors.centerIn: parent
    width: parent.width * 0.7
    height: parent.height * 0.8
    radius: 8
    states: [
        State {
            name: "SELECTED"
            PropertyChanges {
                target: root
                color: root.activeColor
            }
        },
        State {
            name: "IDLE"
            PropertyChanges {
                target: root
                color: "#333"//"grey"
            }
        }
    ]

    Text {
        text: root.text
        anchors.centerIn: parent
        color: "lightgray"
        font.family: labelFont.name;
        font.pointSize: 21
    }
}
