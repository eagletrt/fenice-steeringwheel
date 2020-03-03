import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle{
    id: root

    property var text
    property var selected
    property var index
    property var activated

    FontLoader {id:blackops; source: "../lib/blops.ttf"}

    //border.color: root.selected == 1 ? "lightgrey" : "#000000"
    radius: root.selected == 1 ? "10" : "0"
    color: root.selected == 1 ? "lightgrey" : "transparent"

    Rectangle{
        color: "transparent"
        width: parent.width
        height: parent.height
        anchors.centerIn: parent

        Rectangle{
            color: activated == 1 ? "green" : "lightgrey"
            radius: 100
            anchors.centerIn: parent
            height: parent.height-10
            width: parent.height-10
        }
        
        Text {
            text: root.text
            anchors.centerIn: parent
            font.family: blackops.name
            font.pointSize: 13
            color: "#000000"
        }
    }

        // Rectangle{
        //     color: "transparent"
        //     width: parent.width
        //     height: parent.height/2

        //     Text {
        //         text: root.text
        //         anchors.centerIn: parent
        //         font.family: blackops.name
        //         font.pointSize: 4.5
        //         color: "#ffffff"
        //     }
        // }

}
