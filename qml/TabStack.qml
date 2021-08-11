import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import "tabs"

Item {
    function connect() {
        window.buttonClicked.connect(buttonClickedHandler);
        const currentTab = tabs.children[tabs.currentIndex];
        if (currentTab && currentTab.connect)
            currentTab.connect();

    }

    function disconnect() {
        window.buttonReleased.disconnect(buttonClickedHandler);
        const currentTab = tabs.children[tabs.currentIndex];
        if (currentTab && currentTab.disconnect)
            currentTab.disconnect();

    }

    function buttonClickedHandler(button) {
        if (button === ButtonIds.paddleBottomLeft || button === ButtonIds.paddleBottomRight) {
            if (tabs.blocked)
                return ;

            const total = tabs.children.length;
            const step = button === ButtonIds.paddleBottomLeft ? -1 : +1;
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

    StackLayout {
        id: tabs

        property bool blocked: false

        anchors.fill: parent

        TabTelemetry {
        }

        TabRacing {
        }

        TabCalibration {
        }

        TabStatus {
        }

        TabOverview {
        }

        TabGps {
        }

        TabTerminal {
        }

    }

}
