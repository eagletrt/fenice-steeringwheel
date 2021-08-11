import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
    id: terminal

    property real history: 100
    property string header: "███████╗░█████╗░░██████╗░██╗░░░░░███████╗████████╗██████╗░████████╗
██╔════╝██╔══██╗██╔════╝░██║░░░░░██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝
█████╗░░███████║██║░░██╗░██║░░░░░█████╗░░░░░██║░░░██████╔╝░░░██║░░░
██╔══╝░░██╔══██║██║░░╚██╗██║░░░░░██╔══╝░░░░░██║░░░██╔══██╗░░░██║░░░
███████╗██║░░██║╚██████╔╝███████╗███████╗░░░██║░░░██║░░██║░░░██║░░░
╚══════╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚══════╝░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░
fenice-steering wheel v0.0.1."

    Component.onCompleted: {
        window.onLogsChanged.connect(onLogsChanged);
    }

    function onLogsChanged(line) {
        let logs = terminal.model;
        logs.push(line);
        if (logs.length > history) logs.shift();
        terminal.model = logs;
        scroll.increase();
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
