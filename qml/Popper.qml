import Const 1.0
import QtQuick 2.15

Rectangle {
    id: root

    property int defaultPadding: 40
    property int totalDuration: 550

    signal show(string line, color color)

    color: Style.foreground
    height: 480
    width: 800
    visible: false
    onShow: {
        message.text = line;
        root.color = color;
        if (animation.running)
            animation.restart();
        else
            animation.start();
    }

    SequentialAnimation {
        id: animation

        running: false

        ParallelAnimation {
            PropertyAnimation {
                target: root
                properties: "visible"
                from: false
                to: true
                duration: 0
            }

        }

        ParallelAnimation {
            PropertyAnimation {
                target: root
                properties: "visible"
                from: true
                to: false
                duration: totalDuration
            }

        }

    }

    Text {
        id: message

        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
        color: Style.textInverted
        font: Style.mono.somewhatbig
    }

}
