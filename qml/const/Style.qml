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
    property color darker: "#323232"
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
    property QtObject sizes
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

    sizes: QtObject {
        property string family: monoBold.name
        property int xsmall: 11
        property int small: 12
        property int p: 20
        property int h3: 26
        property int h2: 32
        property int h1: 40
        property int big: 52
        property int verybig: 96
    }

    mono: QtObject {
        property string family: monoBold.name
        property font xsmall: Qt.font({
            "family": monoBold.name,
            "styleName": "Regular",
            "pointSize": sizes.xsmall
        })
        property font small: Qt.font({
            "family": monoBold.name,
            "styleName": "Regular",
            "pointSize": sizes.small
        })
        property font p: Qt.font({
            "family": monoRegular.name,
            "styleName": "Regular",
            "pointSize": sizes.p
        })
        property font h3: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": sizes.h3
        })
        property font h2: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": sizes.h2
        })
        property font h1: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": sizes.h1
        })
        property font big: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": sizes.big
        })
        property font verybig: Qt.font({
            "family": monoBold.name,
            "styleName": "Bold",
            "pointSize": sizes.verybig
        })
    }

    sans: QtObject {
        property string family: sansRegular.name
        property font xsmall: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": 11
        })
        property font small: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": sizes.small
        })
        property font p: Qt.font({
            "family": sansRegular.name,
            "styleName": "Regular",
            "pointSize": sizes.p
        })
        property font h3: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": sizes.h3
        })
        property font h2: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": sizes.h2
        })
        property font h1: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": sizes.h1
        })
        property font big: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": sizes.big
        })
        property font verybig: Qt.font({
            "family": sansBold.name,
            "styleName": "SemiBold",
            "pointSize": sizes.verybig
        })
    }

    status: QtObject {
        property color def: surface
        property color error: red
        property color warn: yellow
        property color ok: green
    }

}
