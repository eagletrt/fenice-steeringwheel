import Const 1.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property int map: 1
    property int barHeight: 6
    property int markerSize: 20
    property var maps: [{
            "name": "0"
        }, {
            "name": "20"
        }, {
            "name": "40"
        }, {
            "name": "60"
        }, {
            "name": "80"
        }, {
            "name": "100"
        }]

    Item {
        anchors.fill: parent
        anchors.leftMargin: 60
        anchors.rightMargin: 60

        ProgressBar {
            id: mapBar

            anchors.fill: parent
            anchors.centerIn: parent
            value: map / 20 / (maps.length - 1)

            background: Item {
            }

            contentItem: Item {
                ColumnLayout {
                    anchors.fill: parent

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Row {
                            anchors.fill: parent

                            Repeater {
                                model: maps

                                Item {
                                    width: mapBar.width / (maps.length - 1)
                                    height: childrenRect.height
                                    anchors.bottom: parent.bottom

                                    Text {
                                        x: -(width / 2)
                                        text: modelData.name
                                        color: Style.text
                                        font: Style.sans.p
                                    }
                                }
                            }
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Rectangle {
                            id: bar

                            width: parent.width
                            height: barHeight
                            color: Style.surface
                        }

                        Rectangle {
                            width: mapBar.visualPosition * parent.width
                            height: barHeight
                            color: Style.yellow
                        }

                        Rectangle {
                            width: mapBar.width / (maps.length - 1)
                            height: barHeight
                            color: map === 0 ? Style.green : Style.dark
                        }

                        Row {
                            width: parent.width
                            height: barHeight

                            Repeater {
                                model: maps

                                Item {
                                    width: mapBar.width / (maps.length - 1)
                                    height: childrenRect.height

                                    Rectangle {
                                        width: markerSize
                                        height: markerSize
                                        x: -(width / 2)
                                        y: bar.y + bar.height / 2 - markerSize / 2
                                        radius: width * 0.5
                                        color: modelData.name === String(root.map) ? (modelData.name === "0" ? Style.green : Style.yellow) : Style.light
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
