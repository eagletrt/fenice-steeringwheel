import Car 1.0
import Const 1.0
import QtQuick 2.0
import QtQuick.Layouts 1.3
import "tabs"
import "tabs/errors"

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
        if (button === Input.paddleBottomLeft || button === Input.paddleBottomRight) {
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

            TabGeneralDebug {
                property string name: "general"
            }

            TabTerminal {
                property string name: "terminal"
            }

            DasErrors {
                property string name: "dasErrors"
            }

            HvErrors {
                property string name: "hvErrors"
            }

            HvFeedbacks {
                property string name: "hvFeedback"
            }

            LvErrors {
                property string name: "lvErrors"
            }

            TabInverters {
                property string name: "tabInverters"
            }

        }

        RowLayout {
            visible: true
            Layout.fillWidth: true
            Layout.maximumHeight: 16
            Layout.minimumHeight: 16
            spacing: 2

            Repeater {
                model: ["general", "terminal", "dasErrors", "hvErrors", "hvFeedback", "lvErrors", "tabInverters"]

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
