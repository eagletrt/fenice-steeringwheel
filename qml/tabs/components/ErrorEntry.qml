import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

RowLayout {
    id: rowLayout

    property string errorText: "default"
    property int error: 0

    Row {
        Rectangle {
            id: rectangle

            width: 18
            height: 18
            color: error === 0 ? "green" : "red"
        }

        Text {
            id: text

            text: errorText
            color: Style.text
            font.pixelSize: 12
        }

    }

}
