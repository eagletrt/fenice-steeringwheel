import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Window {
    id: main

    property var currentIndex: 0

    width: 800
    maximumWidth: 800
    minimumWidth: 800
    height: 480
    maximumHeight: 480
    minimumHeight: 480
    visible: true
    title: qsTr("Steering Wheel") + " #" + currentIndex
    color: "black"

    FontLoader {
        id: valueFont

        source: "qrc:///qml/font/blops.ttf"
    }

    FontLoader {
        id: labelFont

        source: "qrc:///qml/font/blops-chimera-good.ttf"
    }

    Item {
        id: mainwindow

        property var itemOnTop: 1
        property var canSwitchPage: true

        // Buttons signals
        signal btnPressed(int btnID)
        signal btnReleased(int btnID)
        signal btnClicked(int btnID)
        // CAN Signals
        signal carStatusChanged(int statusID)
        signal mapChanged(int mapID)
        signal controlStateChanged(int ctrlIsEnabled, int ctrlIsOn, int warning, int error)
        signal hvStatusChanged(int invRight, int invLeft, int preCharge)

        anchors.fill: parent

        Connections {
            function onBtnClicked(btnID) {
                mainwindow.btnClicked(btnID);
            }

            function onBtnPressed(btnID) {
                mainwindow.btnPressed(btnID);
            }

            function onBtnReleased(btnID) {
                mainwindow.btnReleased(btnID);
            }

            target: Buttons
        }

        MenuPage {
            anchors.fill: parent
            Component.onCompleted: {
                connect();
            }
        }

    }

}
