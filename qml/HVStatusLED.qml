import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "#008000"
    radius: 20
    property var text
    property var selected


    onSelectedChanged: {
        if (root.selected) {
            button.state = "RESET"//START
        } else {
            root.color = "#000000";

            button.state = "NORMAL"
        }
    }

    state: "DEFAULT"

    states: [
        State {
            name: "OK"
            PropertyChanges {
                target: led
                color: "green"
            }
        },
        State {
            name: "NO"
            PropertyChanges {
                target: led
                color: "red"
            }
        },
        State {
            name: "DEFAULT"
            PropertyChanges {
                target: led
                color: "lightgray"
            }
        }
    ]

    Row {
        id: row
        anchors.fill: parent
        spacing: 0

        Rectangle {
            width: root.width * 5/9 //1/2
            height: root.height 
            color: "transparent"

            Text {
                anchors.centerIn: parent
                font.family: labelFont.name;
                text: root.text
                font.pixelSize: 20
                color: "lightgray"
            }
        }

        Rectangle {
            color: "transparent"
            width: root.width * 2/9//1/4
            height: root.height

            Rectangle {
                id: led
                anchors.centerIn: parent
                width: 30
                height: 30
                radius: 30
            }
        }

        Rectangle {
            color: "transparent"
            width: root.width * 2/9//1/4
            height: root.height

            Rectangle {
                id: button

                states: [
                    State {
                        name: "RESET"
                        PropertyChanges {
                            target: button
                            color: "grey"
                        }
                        PropertyChanges {
                            target: text
                            text: "ASK"
                        }
                    },
                    State {
                        name: "NORMAL"
                        PropertyChanges {
                            target: button
                            color: "transparent"
                        }
                        PropertyChanges {
                            target: text
                            color: "transparent"
                        }
                    }
                ]
                anchors.centerIn: parent
                width: parent.width - 20
                height: parent.height - 40
                color: "#888888"
                radius: 5

                Text {
                    id: text
                    font.family: labelFont.name;
                    font.pixelSize: 20
                    anchors.centerIn: parent
                    text: "ASK"
                    color: "lightgrey"
                }
            }
        }
    }
}
