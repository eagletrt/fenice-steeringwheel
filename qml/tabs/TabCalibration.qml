import Const 1.0
import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: calibration

    property int nameWidth: 130
    property int valueWidth: 100
    property string apps: "APPS"
    property string bse: "BSE"
    property string selected: "APPS"

    function connect() {
        window.buttonPressed.connect(onButtonPressed);
        window.buttonReleased.connect(onButtonReleased);
    }

    function disconnect() {
        window.buttonPressed.disconnect(onButtonPressed);
        window.buttonReleased.disconnect(onButtonReleased);
    }

    function onButtonPressed(button) {
        if (button === Input.buttonBottomLeft)
            setmin.color = Qt.darker(setmin.defaultColor, 1.5);
        else if (button === Input.buttonBottomRight)
            setmax.color = Qt.darker(setmax.defaultColor, 1.5);
    }

    function onButtonReleased(button) {
        if (button === Input.buttonBottomLeft) {
            popper.show("MIN SET", Style.foreground);
            setmin.color = setmin.defaultColor;
        } else if (button === Input.buttonBottomRight) {
        } else if (button === Input.paddle) {
        }
    }

    padding: 20

    contentItem: GridLayout {
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        CalibrationBar {
            //             value: Car.das.apps

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: apps
            color: Style.green
            zero: 0
        }

        CalibrationBar {
            //             value: Car.pedals.brake

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: bse
            color: Style.yellow
            zero: 0
        }

        Rectangle {
            id: setmin

            property var defaultColor: Style.blue

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
            id: setmax

            property var defaultColor: Style.orange

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
