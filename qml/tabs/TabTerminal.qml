import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
    id: terminal

    property int history: 100
    property string header: "d88888b d88888b d8b   db d888888b  .o88b. d88888b
88'     88'     888o  88   `88'   d8P  Y8 88'
88ooo   88ooooo 88V8o 88    88    8P      88ooooo
88~~~   88~~~~~ 88 V8o88    88    8b      88~~~~~
88      88.     88  V888   .88.   Y8b  d8 88.
YP      Y88888P VP   V8P Y888888P  `Y88P' Y88888P

>> FENICE STEERING-WHEEL
"

    function onLogsChanged(line) {
        let logs = terminal.model;
        logs.push(line);
        if (logs.length > history)
            logs.shift();
        terminal.model = logs;
        scroll.increase();
    }

    Component.onCompleted: {
        window.onLogsChanged.connect(onLogsChanged);
    }
    flickableDirection: Flickable.VerticalFlick
    boundsBehavior: Flickable.StopAtBounds
    model: header.split("\n")
    clip: true
    spacing: -4 // avoid high padding values for text delegates
    Layout.fillWidth: true
    Layout.fillHeight: true

    delegate: Text {
        color: Style.text
        font: Style.mono.xsmall
        text: modelData
    }

    ScrollBar.vertical: ScrollBar {
        id: scroll

        stepSize: 10
    }
}
