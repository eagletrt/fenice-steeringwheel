import Const 1.0
import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: calibration

    property var sensors: [{
        "name": "APPS",
        "color": Style.green,
        "zero": 0
    }, {
        "name": "BSE",
        "color": Style.red,
        "zero": 0
    }, {
        "name": "STEER",
        "color": Style.yellow,
        "zero": 0.5
    }]
    property int nameWidth: 130
    property int valueWidth: 100

    padding: 20

    contentItem: GridLayout {
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        CalibrationBar {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "APPS"
            color: Style.green
            zero: 0
            value: 0.5
        }

        CalibrationBar {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "STEER"
            color: Style.red
            zero: 0
            value: 0.3
        }

        CalibrationBar {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "BSE"
            color: Style.yellow
            zero: 0.5
            value: 0.8
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Style.blue

            Text {
                anchors.centerIn: parent
                text: "Set Min"
                color: Style.textInverted
                font: Style.sans.h3
            }

        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Style.orange

            Text {
                anchors.centerIn: parent
                text: "Set Max"
                color: Style.textInverted
                font: Style.sans.h3
            }

        }

    }

}
