import Car 1.0
import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3
import "tabs"

Item {
    property var currentTab: tabs.children[tabs.currentIndex]
    property var lastPressed: []
    // V Z C S
    property var fireGameboy: [Input.paddleTopRight, Input.paddleBottomLeft, Input.paddleTopLeft, Input.buttonBottomRight]
    property bool onGameboy: false

    function connect() {
        window.buttonReleased.connect(buttonReleasedHandler);
        const currentTab = tabs.children[tabs.currentIndex];
        if (currentTab && currentTab.connect)
            currentTab.connect();

    }

    function disconnect() {
        window.buttonReleased.disconnect(buttonReleasedHandler);
        const currentTab = tabs.children[tabs.currentIndex];
        if (currentTab && currentTab.disconnect)
            currentTab.disconnect();

    }

    function buttonReleasedHandler(button) {
        lastPressed.push(button);
        if (lastPressed[lastPressed.length - 1] !== fireGameboy[lastPressed.length - 1])
            lastPressed = [];

        if (lastPressed.length === fireGameboy.length && !onGameboy) {
            onGameboy = true;
            const gameboyTab = tabs.children.length - 1;
            const currentTab = tabs.children[tabs.currentIndex];
            if (currentTab.disconnect)
                currentTab.disconnect();

            if (gameboyTab.connect)
                gameboyTab.connect();

            tabs.currentIndex = gameboyTab;
            lastPressed = [];
        } else if (button === Input.paddleBottomLeft || button === Input.paddleBottomRight) {
            onGameboy = false;
            if (tabs.blocked)
                return ;

            const total = tabs.children.length;
            const step = button === Input.paddleBottomLeft ? -1 : +1;
            const index = Utils.mod(tabs.currentIndex + step, total);
            const currentTab = tabs.children[tabs.currentIndex];
            const nextTab = tabs.children[index];
            if (currentTab.disconnect)
                currentTab.disconnect();

            if (nextTab.connect)
                nextTab.connect();

            tabs.currentIndex = index;
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Style.background
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        StackLayout {
            id: tabs

            property bool blocked: false

            Layout.fillWidth: true
            Layout.fillHeight: true

            TabRacing {
                property string name: "racing"
            }

            TabSpeed {
                property string name: "speed"
            }

            TabCalibration {
                property string name: "calibration"
            }

            TabStatus {
                property string name: "status"
            }

            TabGps {
                property string name: "gps"
            }

            TabTerminal {
                property string name: "terminal"
            }

            Item {
                property string name: "emulator"

                function connect() {
                    window.buttonPressed.connect(emulator.button_pressed);
                    window.buttonReleased.connect(emulator.button_released);
                }

                function disconnect() {
                    window.buttonPressed.disconnect(emulator.button_pressed);
                    window.buttonReleased.disconnect(emulator.button_released);
                }

                Emulator {
                    id: emulator

                    width: Style.height * 1.1
                    height: Style.height
                    anchors.centerIn: parent
                }

            }

        }

        RowLayout {
            visible: currentTab.name !== "emulator"
            Layout.fillWidth: true
            Layout.maximumHeight: 16
            Layout.minimumHeight: 16
            spacing: 2

            Repeater {
                model: ["racing", "speed", "calibration", "status", "gps", "terminal"]

                delegate: Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: currentTab.name === modelData ? Style.dark : Style.darker

                    Text {
                        anchors.centerIn: parent
                        text: modelData
                        font.family: Style.sans.family
                        color: Style.text
                    }

                }

            }

        }

    }

}
