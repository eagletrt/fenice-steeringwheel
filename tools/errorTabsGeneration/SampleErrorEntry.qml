import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Frame {
    id: frame

    property string errorText: "default"
    property int error: 0
    property bool valid: true
    property int cols: 1

    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    Layout.preferredWidth: (Style.width - 40) / cols

    Text {
        id: text

        anchors.fill: parent
        text: errorText
        color: Style.darker
        font.pixelSize: 15
    }

    background: Rectangle {
        color: !valid ? Style.yellow : (error === 0) ? Style.green : Style.red
    }

}
