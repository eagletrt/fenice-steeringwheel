//import QtQuick 2.0
import QtQuick.Controls 2.0

import QtQuick 2.4
import QtQuick.Window 2.2

Rectangle {
  FontLoader {id:blackops; source: "../lib/blops.ttf"}
  width: 480
  height: 272
  color: "black"
  id: frame


  Timer {
      interval: 1; running: true; repeat: true
      onTriggered: mainTime.text = new Date().toLocaleTimeString(Qt.locale("it_IT"),"hh:mm:ss")
  }

  Rectangle{
     id: timeRectangle
     color: "black"
     width: 152
     height: 37
     x: 164
     y: 3

     Text {
        id: mainTime
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.family: blackops.name;
        font.pointSize: 13
        color: "lightgray"
     }
  }

  Rectangle {
      width: 370
      height: 220
      x: 55
      y: 52

      id: mainwindow

      property var itemOnTop: 1;
      property var canSwitchPage: true

      // Buttons signals
      signal btnPressed(int btnID)
      signal btnReleased(int btnID)
      signal btnClicked(int btnID)

      // CAN Signals
      signal carStatusChanged(int statusID)
      signal presetChanged(int presetID)
      signal controlStateChanged(int ctrlIsEnabled, int ctrlIsOn, int warning, int error);
      signal hvStatusChanged(int invRight, int invLeft, int preCharge)

      Connections {
          target: Buttons
          onBtnClicked: {
              mainwindow.btnClicked(btnID);
          }
          onBtnPressed: {
              mainwindow.btnPressed(btnID);
          }
          onBtnReleased: {
              mainwindow.btnReleased(btnID);
          }
      }

      StackView {
          anchors.fill: parent
          id: stack

          property Item previusItem

          Component.onCompleted: {
              this.push(page1);
          }

          onCurrentItemChanged: {
              if (previusItem) {
                  if (previusItem.disconnect) {
                      previusItem.disconnect();
                  }
              }

              if (currentItem.connect) {
                  currentItem.connect();
              }

              previusItem = currentItem;
          }

          Component {
              id: page1
              MenuPage {
              }
          }
      }
  }
  StatusFrame{

  }

  HVFrame{

  }

  LVFrame{

  }
}
