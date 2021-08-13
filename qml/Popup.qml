import QtQuick 2.0

Rectangle {
    id: popup

    anchors.centerIn: parent
    color: Style.foreground
    radius: 10
    visible: false
    width: 500
    height: 240

    Connections {
        function onShowPopup(line) {
            popupText.text = line;
            popupAnimation.start();
        }

        target: CarStatus
    }

    SequentialAnimation {
        id: popupAnimation

        running: false

        ParallelAnimation {
            PropertyAnimation {
                target: popup
                properties: "visible"
                from: false
                to: true
                duration: 0
            }

        }

        ParallelAnimation {
            PropertyAnimation {
                target: popup
                properties: "visible"
                from: true
                to: false
                duration: 550
            }

        }

    }

    Text {
        id: popupText

        anchors.centerIn: parent
        color: Style.textInverted
        font: Style.mono.verybig
    }

}
