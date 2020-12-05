import QtQuick 2.12
pragma Singleton

QtObject {
    property int width: 800
    property int height: 480
    property int ledsWidth: 80
    property int ledsHeight: 220
    property color background: "#000000"
    property color foreground: "#FFFFFF"
    property color transparent: "transparent"
    // TODO: check
    property color surface: "#828282"
    property color dark: "#4F4F4F"
    property color light: "#C4C4C4"
    property color text: "#E0E0E0"
    property color accent: orange
    property color red: "#ED5450"
    property color green: "#66BB6A"
    property color yellow: "#F5BB00"
    property color orange: "#F57C03"
    property color blue: "#3D538F"
    property color aqua: "#007EA7"
    property int fontScaling: 2
    property FontLoader monoRegular
    property FontLoader monoBold
    property FontLoader sansRegular
    property FontLoader sansBold
    property QtObject mono
    property QtObject sans
    property QtObject status

    monoRegular: FontLoader {
        source: "qrc:/qml/font/RobotoMono-Regular.ttf"
    }

    monoBold: FontLoader {
        source: "qrc:/qml/font/RobotoMono-Bold.ttf"
    }

    sansRegular: FontLoader {
        source: "qrc:/qml/font/Roboto-Regular.ttf"
    }

    sansBold: FontLoader {
        source: "qrc:/qml/font/Roboto-Bold.ttf"
    }

    mono: QtObject {
        property font p: Qt.font({
            "family": monoRegular.name,
            "styleName": "Regular",
            "pointSize": 20 * fontScaling
        })
        property font h3: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 24 * fontScaling
        })
        property font h2: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 30 * fontScaling
        })
        property font h1: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 36 * fontScaling
        })
    }

    sans: QtObject {
        property font p: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 20 * fontScaling
        })
        property font h3: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 24 * fontScaling
        })
        property font h2: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 30 * fontScaling
        })
        property font h1: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 36 * fontScaling
        })
    }

    status: QtObject {
        property color def: "#828282"
        property color error: "#9A1D1F"
        property color warn: "#F5BB00"
        property color ok: "#3A7D44"
    }

}
