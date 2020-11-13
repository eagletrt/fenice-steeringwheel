import QtQuick 2.7

Rectangle {
    id: pedali

    width: window.width - 20
    height: 27
    color: "transparent"
    x: (window.width - pedali.width) / 2
    y: window.height - pedali.height - 10
    Keys.forwardTo: [acceleratore, freno]

    Rectangle {
        id: acceleratore

        property var value: 0

        width: 0
        height: pedali.height
        color: "blue"
        focus: true
        antialiasing: true
        smooth: true
        Keys.onPressed: {
            if (event.key === Qt.Key_Z)
                acceleratore.width = pedali.width * 75 / 100;

        }
        Keys.onReleased: {
            if (event.key === Qt.Key_Z)
                acceleratore.width = pedali.width * 0 / 100;

        }

        Connections {
            target: Buttons
            onBtnPressed: {
                if (btnID === 1)
                    acceleratore.width = pedali.width * 75 / 100;

            }
            onBtnReleased: {
                if (btnID === 1)
                    acceleratore.width = pedali.width * 0 / 100;

            }
        }

        Behavior on width {
            NumberAnimation {
                duration: 1000
                easing.type: Easing.Linear
                easing.amplitude: 1000
            }

        }

    }

    Rectangle {
        id: capsula

        width: pedali.width * 25 / 100
        height: pedali.height
        color: "transparent"
        x: (pedali.width * 75 / 100)
        states: [
            State {
                name: "fDefault"

                PropertyChanges {
                    target: capsula
                    color: "red"
                }

            }
        ]

        Rectangle {
            id: freno

            width: 0
            height: pedali.height
            color: window.color
            x: parent
            focus: true
            antialiasing: true
            smooth: true
            Keys.onPressed: {
                if (event.key === Qt.Key_X) {
                    capsula.state = "fDefault";
                    freno.width = pedali.width * 0 / 100;
                }
            }
            Keys.onReleased: {
                if (event.key === Qt.Key_X)
                    freno.width = pedali.width * 25 / 100;

            }

            Connections {
                target: Buttons
                onBtnPressed: {
                    if (btnID === 2) {
                        capsula.state = "fDefault";
                        freno.width = pedali.width * 0 / 100;
                    }
                }
                onBtnReleased: {
                    if (btnID === 2)
                        freno.width = pedali.width * 25 / 100;

                }
            }

            Behavior on width {
                NumberAnimation {
                    duration: 1000 / 3
                    easing.type: Easing.Linear
                    easing.amplitude: 1000
                }

            }

        }

    }

}
