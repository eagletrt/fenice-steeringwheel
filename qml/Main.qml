import Const 1.0
import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Window {
    id: main

    property var currentIndex: 0

    width: Style.width
    maximumWidth: Style.width
    minimumWidth: Style.width
    height: Style.height
    maximumHeight: Style.height
    minimumHeight: Style.height
    visible: true
    title: qsTr("Steering Wheel") + " #" + currentIndex

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
