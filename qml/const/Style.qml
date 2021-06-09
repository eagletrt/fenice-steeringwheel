import QtQuick 2.14
pragma Singleton

QtObject {
    property int width: 800
    property int height: 480
    property color background: "#000000"
    property color foreground: "#FFFFFF"
    property color transparent: "transparent"
    property color surface: "#828282"
    property color dark: "#4F4F4F"
    property color light: "#C4C4C4"
    property color text: "#E0E0E0"
    property color textInverted: "#000000"
    property color aqua: "#1abc9c"
    property color green: "#2ECC71"
    property color blue: "#3498DB"
    property color violet: "#9b59b6"
    property color yellow: "#F1C40F"
    property color orange: "#E67E22"
    property color red: "#E74C3C"
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
        source: "qrc:/qml/font/Inter-Regular.ttf"
    }

    sansBold: FontLoader {
        source: "qrc:/qml/font/Inter-SemiBold.ttf"
    }

    mono: QtObject {
        property font xsmall: Qt.font({
            "family": monoBold.name,
            "styleName": "Regular",
            "pointSize": 11
        })
        property font small: Qt.font({
            "family": monoBold.name,
            "styleName": "Regular",
            "pointSize": 14
        })
        property font p: Qt.font({
            "family": monoRegular.name,
            "styleName": "Regular",
            "pointSize": 20
        })
        property font h3: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 26
        })
        property font h2: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 32
        })
        property font h1: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 40
        })
        property font big: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 52
        })
        property font verybig: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": 80
        })
    }

    sans: QtObject {
        property font xsmall: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 11
        })
        property font small: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 14
        })
        property font p: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 20
        })
        property font h3: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": 26
        })
        property font h2: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": 32
        })
        property font h1: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": 40
        })
        property font big: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": 52
        })
        property font verybig: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": 80
        })
    }

    status: QtObject {
        property color def: surface
        property color error: red
        property color warn: yellow
        property color ok: green
    }

}
