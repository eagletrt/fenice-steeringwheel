import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property int currentPreset: CarStatus.preset
    property var presets: [[1, 1], [2, 0], [3, 0], [4, 0], [5, 0], [6, 0]]

    color: "transparent"

    GridLayout {
        anchors.fill: parent
        columns: 6
        columnSpacing: 5

        Repeater {
            model: presets

            Preset {
                index: modelData[0]
                currentIndex: currentPreset
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

        }

    }

}
