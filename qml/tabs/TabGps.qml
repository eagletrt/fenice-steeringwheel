import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    Image {
        anchors.fill: parent
        source: "qrc:/qml/img/satellite/moto-staza-st-raus-novi-marof.png"
    }

    Canvas {
        id: canvas

        property int dotX: 310
        property int dotY: 385
        property int dotSize: 10
        property int dotDelta: 10

        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');
            var x = dotX;
            var y = dotY;
            if (!ctx)
                return ;

            ctx.clearRect(0, 0, Style.width, Style.height);
            ctx.beginPath();
            ctx.fillStyle = Style.orange;
            ctx.ellipse(x - dotDelta / 2, y - dotDelta / 2, dotSize + dotDelta, dotSize + dotDelta);
            ctx.closePath();
            ctx.fill();
            ctx.beginPath();
            ctx.fillStyle = Style.red;
            ctx.ellipse(x, y, dotSize, dotSize);
            ctx.closePath();
            ctx.fill();
        }
    }

    Text {
        anchors.fill: parent
        text: "<b>LAT</b>: 46.155073<br><b>LNG</b>: 16.348283"
        font.family: Style.mono.family
        font.pointSize: Style.sizes.small
        color: Style.text
    }

}
