import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

RowLayout {
    id: rowLayout
    property string errorText: "default"
    property bool error: false

    Row {
        Rectangle {
            id: rectangle

            width: 40
            height: 40
            color: error ? "red" : "green"
        }

        Text {
            id: text

            text: errorText
            color: "white"
            font.pixelSize: 20
        }

    }

}
