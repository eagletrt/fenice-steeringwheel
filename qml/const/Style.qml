import QtQuick 2.12
pragma Singleton

QtObject {
    property int width: 800
    property int height: 480
    property int ledsWidth: 80
    property int ledsHeight: 220
    property color background: "#000000"
    property color surface: "#828282"
    property color dark: "#4F4F4F"
    property color light: "#C4C4C4"
    property color text: "#E0E0E0"
    property color accent: orange
    property color red: "#9A1D1F"
    property color green: "#3A7D44"
    property color yellow: "#F5BB00"
    property color orange: "#F29100"
    property color blue: "#3D538F"
    property color aqua: "#007EA7"
    property FontLoader monoRegular
    property FontLoader monoBold
    property FontLoader sansRegular
    property FontLoader sansBold
    property QtObject mono
    property QtObject sans

    monoRegular: FontLoader {
        source: "qrc:/qml/fonts/RobotoMono-Regular.ttf"
    }

    monoBold: FontLoader {
        source: "qrc:/qml/fonts/RobotoMono-Bold.ttf"
    }

    sansRegular: FontLoader {
        source: "qrc:/qml/fonts/Roboto-Regular.ttf"
    }

    sansBold: FontLoader {
        source: "qrc:/qml/fonts/Roboto-Bold.ttf"
    }

    mono: QtObject {
        property font p: Qt.font({
            "family": monoRegular.name,
            "styleName": "Regular",
            "pointSize": 22
        })
        property font h3: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 60
        })
        property font h2: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 80
        })
        property font h1: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 100
        })
    }

    sans: QtObject {
        property font p: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 22
        })
        property font h4: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 40
        })
        property font h3: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 60
        })
        property font h2: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 80
        })
        property font h1: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 100
        })
    }

}
