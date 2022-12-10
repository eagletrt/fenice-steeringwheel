import Car 1.0
import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    property var currentTab: modes.children[modes.currentIndex]
    property bool onDebug: Car.steering.debug_mode
    property int debugIndex: 1
    property int racingIndex: 0

    function connect() {
        window.buttonReleased.connect(buttonReleasedHandler);
        const currentTab = modes.children[modes.currentIndex];
        if (currentTab && currentTab.connect)
            currentTab.connect();

    }

    function disconnect() {
        window.buttonReleased.disconnect(buttonReleasedHandler);
        const currentTab = modes.children[modes.currentIndex];
        if (currentTab && currentTab.disconnect)
            currentTab.disconnect();

    }

    function buttonReleasedHandler(button) {
    }

    Connections {
        function onDebug_mode_changed(value) {
            if (onDebug) {
                modes.children[racingIndex].disconnect();
                modes.children[debugIndex].connect();
                modes.currentIndex = debugIndex;
            } else {
                modes.children[debugIndex].disconnect();
                modes.children[racingIndex].connect();
                modes.currentIndex = racingIndex;
            }
        }

        target: Car.steering
    }

    Rectangle {
        anchors.fill: parent
        color: Style.background
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        StackLayout {
            id: modes

            Layout.fillWidth: true
            Layout.fillHeight: true

            RacingMode {
            }

            DebugMode {
            }

        }

    }

}
