import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property var text
    property var selected

    color: "#008000"
    radius: 100
    onSelectedChanged: {
        if (root.selected) {
            root.color = "#008000";
            button.state = "RESET"; //START
        } else {
            root.color = "#000000";
            button.state = "NORMAL";
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
            width: root.width * 5 / 9 //1/2
            height: root.height
            color: "transparent"

            Text {
                anchors.centerIn: parent
                font: Style.sans.p
                text: root.text
                color: "lightgray"
            }

        }

        Rectangle {
            color: "transparent"
            width: root.width * 2 / 9 //1/4
            height: root.height

            Rectangle {
                id: led

                anchors.centerIn: parent
                width: 45
                height: 45
                radius: 45
            }

        }

        Rectangle {
            color: "transparent"
            width: root.width * 2 / 9 //1/4
            height: root.height

            Rectangle {
                id: button

                anchors.centerIn: parent
                width: parent.width - 40
                height: parent.height - 100
                color: "#888888"
                radius: 5
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

                Text {
                    id: text

                    font: Style.sans.p
                    anchors.centerIn: parent
                    text: "ASK"
                    color: "lightgrey"
                }

            }

        }

    }

}
