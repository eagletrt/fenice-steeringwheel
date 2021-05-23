import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: gps

    anchors.fill: parent

    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qml/img/satellite/povo-1-parking.png"
    }

    Canvas {
        id: canvas

        property int dotX: Style.width / 2
        property int dotY: Style.height / 2
        property int t: 1
        property int dotSize: 10
        property int dotDelta: 10

        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');
            var x = dotX + Math.cos(t / 100) * 100;
            var y = dotY + Math.sin(t / 100) * 100;
            if (!ctx)
                return ;

            ctx.clearRect(0, 0, Style.width, Style.height);
            ctx.beginPath();
            ctx.fillStyle = Style.orange;
            ctx.ellipse(x - dotDelta / 2, y - dotDelta / 2, dotSize + dotDelta, dotSize + dotDelta);
            ctx.closePath();
            ctx.fill();
            ctx.beginPath();
            ctx.fillStyle = Style.yellow;
            ctx.ellipse(x, y, dotSize, dotSize);
            ctx.closePath();
            ctx.fill();
        }

        Timer {
            interval: 16
            repeat: true
            running: true
            onTriggered: {
                canvas.requestPaint();
            }
        }

        NumberAnimation on t {
            from: 1
            to: 2 * 314
            duration: 1000
            easing.type: Easing.InOutQuad
            loops: Animation.Infinite
        }

    }

}
