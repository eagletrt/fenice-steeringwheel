import Const 1.0
import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "components"

Control {
    id: root

    property int nameWidth: 130
    property int valueWidth: 100
    property int selected: 0
    property int lenght: 3

    function connect() {
        window.buttonReleased.connect(onButtonReleased);
    }

    function disconnect() {
        window.buttonReleased.disconnect(onButtonReleased);
    }

    function onButtonReleased(button) {
        if (button === Input.buttonBottomLeft) {
            set("MIN");
            popper.show("MIN SET", Style.foreground);
        } else if (button === Input.buttonBottomRight) {
            set("MAX");
            popper.show("MAX SET", Style.foreground);
        } else if (button === Input.paddleTopLeft)
            selected = Utils.mod(selected - 1, lenght);
        else if (button === Input.paddleTopRight)
            selected = Utils.mod(selected + 1, lenght);
    }

    function set(bound) {
        if (root.selected === 0)
            Car.das.send_set_pedal_range(0, bound === "MAX" ? 0 : 1);

        if (root.selected === 1)
            Car.das.send_set_pedal_range(1, bound === "MAX" ? 0 : 1);
        else
            Car.das.send_set_steering_angle_range(bound === "MAX" ? 1 : 0);
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
            value: (Car.das.steering_angle + 7) / 1.97
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
