import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
    id: terminal

    property string header: "███████╗░█████╗░░██████╗░██╗░░░░░███████╗████████╗██████╗░████████╗
██╔════╝██╔══██╗██╔════╝░██║░░░░░██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝
█████╗░░███████║██║░░██╗░██║░░░░░█████╗░░░░░██║░░░██████╔╝░░░██║░░░
██╔══╝░░██╔══██║██║░░╚██╗██║░░░░░██╔══╝░░░░░██║░░░██╔══██╗░░░██║░░░
███████╗██║░░██║╚██████╔╝███████╗███████╗░░░██║░░░██║░░██║░░░██║░░░
╚══════╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚══════╝░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░
fenice-steering wheel v0.0.1."

    function connect() {
        window.onLogsChanged.connect(onLogsChanged);
        scroll.increase();
    }

    function disconnect() {
        window.onLogsChanged.disconnect(onLogsChanged);
    }

    function onLogsChanged(line) {
        scroll.increase();
    }

    flickableDirection: Flickable.VerticalFlick
    boundsBehavior: Flickable.StopAtBounds
    model: 50000
    clip: true
    Layout.fillWidth: true
    Layout.fillHeight: true

    delegate: ItemDelegate {
        text: modelData
    }

    ScrollBar.vertical: ScrollBar {
        id: scroll

        stepSize: 10
    }

}
