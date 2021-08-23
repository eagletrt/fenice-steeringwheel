import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.12

Item {
    id: overview

    Image {
        id: car
        source: "qrc:/qml/img/fenice.png"
    }

    // Rectangle {
    //     id: tireFrontRight
    //     x: 260
    //     y: 100
    //     width: 100
    //     height: 100
    //     color: Style.red
    //     visible: false
    // }

    // OpacityMask {
    //     cached: true
    //     anchors.fill: tireFrontRight
    //     source: tireFrontRight
    //     maskSource: car
    // }
}
