import QtQuick 2.12
pragma Singleton

QtObject {
    // error
    // green
    // outdated
    // default

    property QtObject sensor

    sensor: QtObject {
        property int error: 0
        property int ok: 1
        property int outdated: 2
        property int def: 3
        property var colors: [Style.red, Style.green, Style.yellow, Style.dark]
    }

}
