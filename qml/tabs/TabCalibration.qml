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
    property int selected: 0
    property int lenght: 3

    function connect() {
        window.buttonPressed.connect(onButtonPressed);
        window.buttonReleased.connect(onButtonReleased);
    }

    function disconnect() {
        window.buttonPressed.disconnect(onButtonPressed);
        window.buttonReleased.disconnect(onButtonReleased);
    }

    function onButtonPressed(button) {
        if (button === Input.buttonTopLeft)
            setmin.color = Qt.darker(setmin.defaultColor, 1.4);
        else if (button === Input.buttonTopRight)
            setmax.color = Qt.darker(setmax.defaultColor, 1.4);
    }

    function onButtonReleased(button) {
        // send message
        // send message
        if (button === Input.buttonBottomLeft) {
            setmin.color = setmin.defaultColor;
            popper.show("MIN SET", Style.foreground);
        } else if (button === Input.buttonBottomRight) {
            setmax.color = setmax.defaultColor;
            popper.show("MAX SET", Style.foreground);
        } else if (button === Input.paddleBottomLeft)
            selected = Utils.mod(selected + 1, lenght);
        else if (button === Input.paddleBottomRight)
            selected = Utils.mod(selected - 1, lenght);
    }

    padding: 20

    contentItem: GridLayout {
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        CalibrationBar {
            value: Car.das.apps
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "APPS"
            color: Style.green
            background: selected == 0 ? Style.surface : Qt.darker(Style.surface, 1.4)
            zero: 0
        }

        CalibrationBar {
            value: Car.das.bse
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "BSE"
            color: Style.yellow
            background: selected == 1 ? Style.surface : Qt.darker(Style.surface, 1.4)
            zero: 0
        }

        CalibrationBar {
            value: Car.das.steering_angle
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "STEER"
            color: Style.red
            background: selected == 2 ? Style.surface : Qt.darker(Style.surface, 1.4)
            zero: 0.5
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
