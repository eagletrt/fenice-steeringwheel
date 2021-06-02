import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Flickable {
    id: terminal

    property string header: "███████╗░█████╗░░██████╗░██╗░░░░░███████╗████████╗██████╗░████████╗
██╔════╝██╔══██╗██╔════╝░██║░░░░░██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝
█████╗░░███████║██║░░██╗░██║░░░░░█████╗░░░░░██║░░░██████╔╝░░░██║░░░
██╔══╝░░██╔══██║██║░░╚██╗██║░░░░░██╔══╝░░░░░██║░░░██╔══██╗░░░██║░░░
███████╗██║░░██║╚██████╔╝███████╗███████╗░░░██║░░░██║░░██║░░░██║░░░
╚══════╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚══════╝░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░
fenice-steering wheel v0.0.1."

    function connect() {
        textbox.text = header + "\n" + Steering.logs.join("\n");
        window.onLogsChanged.connect(onLogsChanged);
        scroll.increase()
    }

    function disconnect() {
        window.onLogsChanged.disconnect(onLogsChanged);
    }

    function onLogsChanged(line) {
        textbox.text += "\n" + line;
        scroll.increase()
    }

    TextArea.flickable: TextArea {
        id: textbox
        readOnly: true
        wrapMode: Text.WordWrap
        color: Style.text
        font: Style.mono.xsmall
        text: header
    }

    ScrollBar.vertical: ScrollBar {
        stepSize: 10
        id: scroll
    }
}
