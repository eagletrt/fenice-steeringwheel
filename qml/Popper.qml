import Const 1.0
import QtQuick 2.15

Rectangle {
    id: root

    property int defaultPadding: 40
    property int totalDuration: 550

    signal show(string line)

    color: Style.foreground
    radius: 10
    visible: false
    onShow: {
        metrics.text = line;
        root.width = metrics.boundingRect.width + defaultPadding;
        root.height = metrics.boundingRect.height;
        message.text = line;
        if (animation.running)
            animation.restart();
        else
            animation.start();
    }

    TextMetrics {
        id: metrics

        font: Style.mono.verybig
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

        anchors.centerIn: parent
        color: Style.textInverted
        font: Style.mono.verybig
    }

}
