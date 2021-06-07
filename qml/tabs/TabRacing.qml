import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"

Rectangle {
    id: racing

    property int columnWidth: 100

    function connect() {
        window.onMapChanged.connect(onMapChanged);
        mapBar.map = Math.min(CarStatus.map, mapBar.maps.length - 1);
    }

    function disconnect() {
        window.onMapChanged.disconnect(onMapChanged);
    }

    function onMapChanged(map) {
        mapBar.map = Math.min(map, mapBar.maps.length - 1);
    }

    color: Style.background

    Timer {
        property real start: Date.now()

        interval: 10
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: function update() {
            let d = new Date(Date.now() - start);
            time.text = String(d.getUTCMinutes()).padStart(2, "0") + ":" + String(d.getUTCSeconds()).padStart(2, "0") + "." + String((Math.min(99, d.getUTCMilliseconds() / 10)).toFixed()).padStart(2, "0");
        }
    }

    RowLayout {
        anchors.fill: parent

        ValueColumn {
            Layout.fillHeight: true
            Layout.minimumWidth: racing.columnWidth
            label: "[V] Porco"
            direction: Qt.LeftToRight
            barCount: 8

            columnGradient: Gradient {
                GradientStop {
                    position: 1
                    color: Style.red
                }

                GradientStop {
                    position: 0
                    color: Style.orange
                }

            }

            SequentialAnimation on value {
                loops: Animation.Infinite

                NumberAnimation {
                    from: 0
                    to: 1
                    duration: 2500
                }

                NumberAnimation {
                    from: 1
                    to: 0
                    duration: 2500
                }

            }

        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: Style.background

            ColumnLayout {
                anchors.fill: parent

                Item {
                    Layout.minimumHeight: childrenRect.height
                    Layout.fillWidth: true

                    Text {
                        id: time

                        anchors.centerIn: parent
                        color: Style.text
                        font: Style.mono.big
                    }

                }

                Item {
                    Layout.minimumHeight: 100
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "°C"
                                label: "L. INVERTER"

                                SequentialAnimation on value {
                                    loops: Animation.Infinite

                                    NumberAnimation {
                                        from: 45
                                        to: 35
                                        duration: 500
                                    }

                                    NumberAnimation {
                                        from: 35
                                        to: 45
                                        duration: 500
                                    }

                                }

                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "°C"
                                label: "T. PORCO"

                                SequentialAnimation on value {
                                    loops: Animation.Infinite

                                    NumberAnimation {
                                        from: 25
                                        to: 35
                                        duration: 800
                                    }

                                    NumberAnimation {
                                        from: 35
                                        to: 25
                                        duration: 800
                                    }

                                }

                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ValueLabel {
                                unit: "°C"
                                label: "R. INVERTER"

                                SequentialAnimation on value {
                                    loops: Animation.Infinite

                                    NumberAnimation {
                                        from: 35
                                        to: 45
                                        duration: 500
                                    }

                                    NumberAnimation {
                                        from: 45
                                        to: 35
                                        duration: 500
                                    }

                                }

                            }

                        }

                    }

                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            BigValue {
                                unit: "wh\nkm"

                                SequentialAnimation on value {
                                    loops: Animation.Infinite

                                    NumberAnimation {
                                        from: 150
                                        to: 50
                                        duration: 1500
                                    }

                                    NumberAnimation {
                                        from: 50
                                        to: 150
                                        duration: 1500
                                    }

                                }

                            }

                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            BigValue {
                                unit: "km\nh"

                                SequentialAnimation on value {
                                    loops: Animation.Infinite

                                    NumberAnimation {
                                        from: 50
                                        to: 150
                                        duration: 1500
                                    }

                                    NumberAnimation {
                                        from: 150
                                        to: 50
                                        duration: 1500
                                    }

                                }

                            }

                        }

                    }

                }

                Item {
                    Layout.minimumHeight: 80
                    Layout.fillWidth: true

                    MapBar {
                        id: mapBar
                    }

                }

            }

        }

        ValueColumn {
            Layout.fillHeight: true
            Layout.minimumWidth: racing.columnWidth
            label: "[kw] Porco"
            direction: Qt.RightToLeft
            barCount: 8

            columnGradient: Gradient {
                GradientStop {
                    position: 1
                    color: Style.blue
                }

                GradientStop {
                    position: 0
                    color: Style.aqua
                }

            }

            SequentialAnimation on value {
                loops: Animation.Infinite

                NumberAnimation {
                    from: 1
                    to: 0
                    duration: 2500
                }

                NumberAnimation {
                    from: 0
                    to: 1
                    duration: 2500
                }

            }

        }

    }

}
