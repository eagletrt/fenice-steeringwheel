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
            popper.show("MIN SET");
            setmin.color = setmin.defaultColor;
        } else if (button === Input.buttonBottomRight) {
            popper.show("MAX SET");
            setmax.color = setmax.defaultColor;
        }
    }

    padding: 20

    contentItem: GridLayout {
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        CalibrationBar {
            // value: Car.pedals.apps

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "APPS"
            color: Style.green
            zero: 0
        }

        CalibrationBar {
            // value: Car.pedals.steer

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "STEER"
            color: Style.red
            zero: 0.5
        }

        CalibrationBar {
            // value: Car.pedals.bse

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            name: "BSE"
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
