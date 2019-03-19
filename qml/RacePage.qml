import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Rectangle {
    id: window
    color: "black"

    Pedali {
        id: pedali
    }

    Rectangle {
        id: centro
        width: 300
        height: 180
        color: "transparent"
        anchors.centerIn: parent

        Rectangle {
            color: "green"
            height: parent.height
            Column {
                width: 50
                spacing: 6

                id: presets1

                Repeater {
                    model: 4

                    Rectangle {
                        width: 50
                        height: 40
                        color: "grey"

                        Text {
                            text: "q" + index
                            anchors.centerIn: parent
                        }

                    }
                }
            }
        }

        VelocityGauge {
            id: velocita
            color: "red"
        }

        Column {
            width: 50
            x: presets1.width + velocita.width
            spacing: 6

            Component.onCompleted: {
                console.log(this.x);
                console.log(presets1.width + velocita.width);
            }

            Repeater {
                model: 4

                Rectangle {
                    width: 50
                    height: 40
                    color: "grey"

                    Text {
                        text: "q" + index
                        anchors.centerIn: parent
                    }

                }
            }
        }

    }


    Rectangle {
        id: tempo
        width: velocita.width
        height: 27
        color: "transparent"
        x: (window.width-tempo.width)/2
        y: 10

        Rectangle {
            id: minA
            width: tempo.width/8
            height: tempo.height
            color: "lightgray"
        }

        Rectangle {
            id: minB
            width: minA.width
            height: tempo.height
            color: "lightgray"
            x: minA.width*8/7
        }

        Rectangle {
            id: dpA
            width: minA.width*25/56
            height: tempo.height
            color: "transparent"
            x: minB.x+minA.width*150/128

            Text {
                text: ":"
                anchors.centerIn: parent
                color: "lightgray"
                font.pointSize: 17
                font.family: "BlackOpsOne"
            }
        }

        Rectangle {
            id: secA
            width: minA.width
            height: tempo.height
            color: "lightgray"
            x: minB.x+minA.width*25/14
        }

        Rectangle {
            id: secB
            width: minA.width
            height: tempo.height
            color: "lightgray"
            x: secA.x+minA.width*8/7
        }

        Rectangle {
            id: dpB
            width: minA.width*25/56
            height: tempo.height
            color: "transparent"
            x: secB.x+minA.width*150/128

            Text {
                text: ":"
                anchors.centerIn: parent
                color: "lightgray"
                font.pointSize: 17
                font.family: "BlackOpsOne"
            }
        }

        Rectangle {
            id: msecA
            width: minA.width
            height: tempo.height
            color: "lightgray"
            x: secB.x+minA.width*25/14
        }

        Rectangle {
            id: msecB
            width: minA.width
            height: tempo.height
            color: "lightgray"
            x: msecA.x+minA.width*8/7
        }
    }

    Rectangle {
        id: pm
        width: q1.width
        height: tempo.height
        color: "transparent"
        x: lvTemp.x-pm.width-10
        y: tempo.y

        Rectangle {
            id: piu
            width: pm.width/2
            height: pm.height
            color: "transparent"

            Text {
                text: "+"
                anchors.centerIn: parent
                color: "red"
                font.pointSize: 20
                font.family: "BlackOpsOne"
            }
        }

        Rectangle {
            id: meno
            width: piu.width
            height: pm.height
            color: "transparent"
            x: piu.width

            Text {
                text: "-"
                anchors.centerIn: parent
                color: "green"
                font.pointSize: 20
                font.family: "BlackOpsOne"
            }
        }
    }

    Rectangle {
        id: hvTemp
        width: hvBatterie.width
        height: tempo.height
        color: "transparent"
        x: hvBatterie.x
        y: tempo.y

        Rectangle {
           id: hvVal
           width: hvTemp.width/2
           height: hvTemp.height
           color: "lightgray"
        }

        Rectangle {
            id: hvTesto
            width: hvTemp.width/2-5
            height: hvTemp.height
            color: "transparent"
            x: hvVal.width+5

            Text {
                text: "°C"
                anchors.centerIn: parent
                color: "lightgray"
                font.pointSize: 15
                font.family: "BlackOpsOne"
            }
        }
    }

    Rectangle {
        id: lvTemp
        width: lvBatterie.width
        height: tempo.height
        color: "transparent"
        x: lvBatterie.x
        y: tempo.y

        Rectangle {
           id: lvVal
           width: lvTemp.width/2
           height: lvTemp.height
           color: "lightgray"
        }

        Rectangle {
            id: lvTesto
            width: lvTemp.width/2-5
            height: lvTemp.height
            color: "transparent"
            x: lvVal.width+5

            Text {
                text: "°C"
                anchors.centerIn: parent
                color: "lightgray"
                font.pointSize: 15
                font.family: "BlackOpsOne"
            }
        }
    }
}
