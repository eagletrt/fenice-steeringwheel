import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property var text
    property var barColor
    property var barValue
    property var selected

    color: root.selected === 1 ? "green" : menu.color
    radius: root.selected === 1 ? "100" : "0"

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.preferredWidth: parent.width * 1 / 8
            Layout.preferredHeight: parent.height / 5
            Layout.fillWidth: true
            Layout.fillHeight: false
            color: "transparent"

            Text {
                text: root.text
                font: Style.sans.p
                color: "lightgray"
                anchors.centerIn: parent
            }

        }

        Rectangle {
            Layout.preferredWidth: parent.width * 3 / 8
            Layout.preferredHeight: parent.height / 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            Rectangle {
                width: parent.width - 50
                height: parent.height / 3
                anchors.centerIn: parent
                border.width: 1
                border.color: "lightgray"
                color: menu.color

                Rectangle {
                    width: root.barValue
                    height: parent.height - 2
                    anchors.left: parent.left
                    anchors.leftMargin: 1
                    anchors.verticalCenter: parent.verticalCenter
                    color: root.barColor
                }

            }

        }

    }

}
