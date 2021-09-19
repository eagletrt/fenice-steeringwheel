import Const 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int value
    property string unit
    property string label

    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Item {
                    Layout.fillWidth: true
                }

                Text {
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    text: String(root.value).padStart(2, " ")
                    color: Style.text
                    font: Style.mono.h2
                }

                Text {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    text: root.unit
                    color: Style.text
                    font: Style.sans.p
                }

                Item {
                    Layout.fillWidth: true
                }

            }

        }

        Item {
            Layout.fillWidth: true
            Layout.minimumHeight: childrenRect.height

            Text {
                anchors.centerIn: parent
                text: root.label
                color: Style.text
                font: Style.sans.small
            }

        }

    }

}
