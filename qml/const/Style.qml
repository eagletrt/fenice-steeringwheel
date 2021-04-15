import QtQuick 2.14
pragma Singleton

QtObject {
    property int width: 800
    property int height: 480
    property int ledsWidth: 80
    property int ledsHeight: 220
    property color background: "#000000"
    property color foreground: "#FFFFFF"
    property color transparent: "transparent"
    property color surface: "#6B7280"
    property color dark: "#4F4F4F"
    property color light: "#C4C4C4"
    property color text: "#E0E0E0"
    property color red: "#E74C3C"
    property color green: "#2ECC71"
    property color orange: "#E67E22"
    property color yellow: "#F1C40F"
    property color blue: "#3498DB"
    property color aqua: "#1abc9c"
    property int fontScaling: 1
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
        property font small: Qt.font({
            "family": monoBold.name,
            "styleName": "Regular",
            "pointSize": 14 * fontScaling
        })
        property font p: Qt.font({
            "family": monoRegular.name,
            "styleName": "Regular",
            "pointSize": 20 * fontScaling
        })
        property font h3: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 27 * fontScaling
        })
        property font h2: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 32 * fontScaling
        })
        property font h1: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 40 * fontScaling
        })
        property font big: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 52 * fontScaling
        })
        property font verybig: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 80 * fontScaling
        })
    }

    sans: QtObject {
        property font small: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 14 * fontScaling
        })
        property font p: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 20 * fontScaling
        })
        property font h3: Qt.font({
            "family": sansRegular.name,
            "styleName": "Bold",
            "pointSize": 27 * fontScaling
        })
        property font h2: Qt.font({
            "family": sansRegular.name,
            "styleName": "Bold",
            "pointSize": 32 * fontScaling
        })
        property font h1: Qt.font({
            "family": sansRegular.name,
            "styleName": "Bold",
            "pointSize": 40 * fontScaling
        })
        property font big: Qt.font({
            "family": sansRegular.name,
            "styleName": "Bold",
            "pointSize": 52 * fontScaling
        })
        property font verybig: Qt.font({
            "family": sansRegular.name,
            "styleName": "Bold",
            "pointSize": 80 * fontScaling
        })
    }

    status: QtObject {
        property color def: "#828282"
        property color error: "#E74C3C"
        property color warn: "#F1C40F"
        property color ok: "#2ECC71"
    }

}
