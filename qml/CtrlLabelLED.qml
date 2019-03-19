import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "#000000"

    // Command to activate the control
    property var active
    // Flag for checking wheater the ctrl is currently running
    property var enabled
    property int ctrlStatus: CarStatus.CTRLEnabled

    onEnabledChanged: {
    }

    onCtrlStatusChanged: {
        console.log("Controllo cambiato!");
        console.log(ctrlStatus);
        this.state = ctrlStatus ? 'enabled' : 'disabled';

    }

    states: [
        State {
            name: "enabled"
            PropertyChanges {
                target: spindle
                color: "green"
            }
            AnchorChanges {
                target: spindle
                anchors.right: undefined
                anchors.left: slider_cont.left
            }
        },
        State {
            name: "disabled"
            PropertyChanges {
                target: spindle
                color: "grey"
            }
            AnchorChanges {
                target: spindle
                anchors.left: undefined
                anchors.right: slider_cont.right
            }
        }
    ]

    Row {
        anchors.fill: parent

        Rectangle {
            color: "#000000"
            width: root.width * 1/5
            height: root.height

            Rectangle {
                id: slider_cont
                width: parent.width * 0//0.9
                height: parent.height * 0//0.5
                anchors.centerIn: parent
                color: "#000000"
                border.width: 2
                border.color: ctrlStatus ? 'green' : "gray"
                radius: 10

                Rectangle {
                    id: spindle
                    width: parent.height - 6
                    height: parent.height - 6
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 3
                    anchors.rightMargin: 3
                    radius: 40
                }
            }
        }

        LabelLED {
            text: "CTRL"
            ledColor: "purple"
            width: root.width * 2/3
            height: root.height
            state: root.active ? 'on' : 'off'
        }
    }
}
