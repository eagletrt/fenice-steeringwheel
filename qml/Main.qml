// Main.qml load all the components
// TimerLabel, HVBar, LVBar
// MenuPage with all the tabs and StatusBar with idle, start, run, and telemetry

import QtQuick 2.4
// import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Window {
    //    Timer {
    //        id: tim1
    //        interval: 1000
    //        running: true
    //        repeat: true
    //        onTriggered: {
    //            secInt[1]++;
    //            if (secInt[1] > 9) {
    //                secInt[0]++;
    //                secInt[1] = 0;
    //                if (secInt[0] > 5) {
    //                    secInt[0] = 0;
    //                    minInt[1]++;
    //                }
    //            }
    //            if (minInt[1] > 9) {
    //                minInt[1] = 0;
    //                minInt[0]++;
    //                if (minInt[0] > 5) {
    //                    minInt[0] = 0;
    //                    hourInt[1]++;
    //                }
    //            }
    //            if (hourInt[1] > 9) {
    //                hourInt[1] = 0;
    //                hourInt[0]++;
    //            }
    //            timeString = hourInt[0].toString() + hourInt[1].toString() + ":" + minInt[0].toString() + minInt[1].toString() + ":" + secInt[0].toString() + secInt[1].toString();
    //            mainTime.text = timeString;
    //        }
    //        Component.onCompleted: {
    //            timeString = hourInt[0].toString() + hourInt[1].toString() + ":" + minInt[0].toString() + minInt[1].toString() + ":" + secInt[0].toString() + secInt[1].toString();
    //            mainTime.text = timeString;
    //        }
    //    }
    //    Rectangle {
    //        id: timeRectangle
    //        color: "transparent"
    //        width: 275
    //        height: 60
    //        x: 265
    //        y: 3
    //        Text {
    //            id: mainTime
    //            anchors.horizontalCenter: parent.horizontalCenter
    //            anchors.verticalCenter: parent.verticalCenter
    //            font.family: valueFont.name
    //            font.pointSize: 50
    //            color: "lightgray"
    //        }
    //    }

    // color: "purple"
    id: frame

    property string timeString
    property var secInt: [0, 0]
    property var minInt: [0, 0]
    property var hourInt: [0, 0]

    width: 800
    maximumWidth: 800
    minimumWidth: 800
    height: 480
    maximumHeight: 480
    minimumHeight: 480
    visible: true
    color: "black"

    FontLoader {
        id: valueFont

        source: "qrc:///qml/font/blops.ttf"
    }

    FontLoader {
        id: labelFont

        source: "qrc:///qml/font/blops-chimera-good.ttf"
    }

    Rectangle {
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
        color: "transparent"
        z: 2

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

        StackView {
            id: stack

            property Item previusItem

            anchors.fill: parent
            Component.onCompleted: {
                this.push(page1);
            }
            onCurrentItemChanged: {
                if (previusItem) {
                    if (previusItem.disconnect)
                        previusItem.disconnect();

                }
                if (currentItem.connect)
                    currentItem.connect();

                previusItem = currentItem;
            }

            Component {
                id: page1

                MenuPage {
                }

            }

        }

    }

}
