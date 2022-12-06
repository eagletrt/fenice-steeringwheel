import Car 1.0
import Const 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Text {
    id: car_status

    Layout.alignment: Qt.AlignCenter
    Layout.columnSpan: 2
    font: Style.sans.somewhatbig
    color: Style.text
    states: [
        State {
            name: "IDLE"
            when: Car.das.car_status === 0

            PropertyChanges {
                target: car_status
                text: "IDLE"
            }

        },
        State {
            name: "PRE SETUP"
            when: Car.das.car_status === 1

            PropertyChanges {
                target: car_status
                text: "PRE SETUP"
            }

        },
        State {
            name: "TS ON"
            when: Car.das.car_status === 2

            PropertyChanges {
                target: car_status
                text: "TS ON"
            }

        },
        State {
            name: "POST SETUP"
            when: Car.das.car_status === 3

            PropertyChanges {
                target: car_status
                text: "POST SETUP"
            }

        },
        State {
            name: "DRIVE"
            when: Car.das.car_status === 4

            PropertyChanges {
                target: car_status
                text: "DRIVE"
            }

        },
        State {
            name: "TEARDOWN"
            when: Car.das.car_status === 5

            PropertyChanges {
                target: car_status
                text: "TEARDOWN"
            }

        },
        State {
            name: "???"
            when: true

            PropertyChanges {
                target: car_status
                text: "???"
            }

        }
    ]
}
