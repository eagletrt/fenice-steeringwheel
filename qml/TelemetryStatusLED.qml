import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "transparent"

    state: "0" //UNSELECTED

    FontLoader {id:blackops; source: "../lib/blops.ttf"}

    property var text
    property var selected
    
    Rectangle{
        id: row
        color: "transparent"
        border.color: selected == 1 ? "lightgrey" : "transparent"
        radius: selected == 1 ? "5" : "0"
        width: parent.width
        height: parent.height
        anchors.centerIn: parent

        Rectangle{
            id: led
            color: "transparent"
            radius: 100
            anchors.centerIn: parent
            height: parent.height-10
            width: parent.height-10
        }
        
        Text {
            id: sensor
            text: root.text
            anchors.centerIn: parent
            font.family: blackops.name
            font.pointSize: 18
            color: "lightgrey"
        }
    }

    states: [
        State {
            name: "0" //UNSELECTED
            PropertyChanges {
                target: led
                border.color: "#000"
            }
        },
        State {
            name: "1" //SELECTED
            PropertyChanges {
                target: led
                border.color: "green"
            }
        }
    ]
}
