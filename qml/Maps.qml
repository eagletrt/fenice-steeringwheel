import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "transparent"

    property int currentMap: CarStatus.map
    property var maps: [
        [1, 1],
        [2, 0],
        [3, 0],
        [4, 0],
        [5, 0],
        [6, 0],
    ]

    GridLayout {
        anchors.fill: parent
        columns: 6
        columnSpacing: 5

        Repeater {
            model: maps
            Map {
                index: modelData[0]
                currentIndex: currentMap
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
