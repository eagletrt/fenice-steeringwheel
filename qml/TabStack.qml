import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3
import "tabs"

Item {
    property var currentTab: tabs.children[tabs.currentIndex]

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
        if (button === Input.paddleTopLeft || button === Input.paddleTopRight) {
            if (tabs.blocked)
                return ;

            const total = tabs.children.length;
            const step = button === Input.paddleTopLeft ? -1 : +1;
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

            TabStatus {
                property string name: "status"
            }

            TabOverview {
                property string name: "overview"
            }

            TabGps {
                property string name: "gps"
            }

            TabTerminal {
                property string name: "terminal"
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 16
            Layout.minimumHeight: 16
            spacing: 2

            Repeater {
                model: ["racing", "speed", "status", "overview", "gps", "terminal"]

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
