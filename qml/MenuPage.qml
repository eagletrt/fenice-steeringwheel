import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Rectangle {
  id: menu
  color: "#000000"
  property var steeringWheelPopup: CarStatus.SteeringWheelPopup;
  property var animationDuration: 0;
  property var buttonsClick: true;
  property var col;
  property var priority;

  signal btnPressed(int btnID)
  signal btnReleased(int btnID)
  signal btnClicked(int btnID)

  FontLoader {id:blackops; source: "../lib/blops.ttf"}


  function connect() {
    mainwindow.btnPressed.connect(btnPressedHandler);
    mainwindow.btnReleased.connect(btnReleasedHandler);
    mainwindow.btnClicked.connect(btnClickedHandler);
  }

  function disconnect() {
    mainwindow.btnPressed.disconnect(btnPressedHandler);
    mainwindow.btnReleased.disconnect(btnReleasedHandler);
    mainwindow.btnClicked.disconnect(btnClickedHandler);

    // Disconnect current tab, prevent erroneous btn click handling
    var currentTab = tabView.getTab(0);

    if (currentTab && currentTab.children[0].disconnect) {
      currentTab.children[0].disconnect();
    }
  }

  function btnPressedHandler(btnID) {
    menu.btnPressed(btnID);
  }

  function btnReleasedHandler(btnID) {
    menu.btnReleased(btnID);
  }

  function btnClickedHandler(btnID) {
    menu.btnClicked(btnID);
  }

  onSteeringWheelPopupChanged: {
    steeringWheelPopup.toUpperCase();

    col = steeringWheelPopup[1];
    priority = steeringWheelPopup[0];

    //Set up the color
    if(col == 'B') {
      popup.color = "blue";
    } 
    else if (col == 'G') {
      popup.color = "green";
    } 
    else if (col == 'Y') {
      popup.color = 'yellow';
      popupText.color = "#000";
    } 
    else {
      popup.color = '#000';
    }

    //Set up the priority
    if(priority == 0) {
      animationDuration = 500
      popup.visible = true;
      tabView.visible = false;
      buttonsClick = false;
      popupStatic.start();
    } 
    else if(priority == 1) {
      popup.visible = true;
      tabView.visible = false;
      buttonsClick = false
      animationDuration = 700
      popupStatic.start();
    } 
    else if(priority == 2) {
      popup.visible = true;
      tabView.visible = false;
      buttonsClick = false;
    } else {
      console.log("Priority has to be a number in the range of [0, 2]")
    }

    //Set up text
    popupText.text = steeringWheelPopup.slice(2);

    //popupText.text = decoder[steeringWheelPopup];
//
    //if(steeringWheelPopup >= 0 && steeringWheelPopup <= 2) {
    //  
    //  if(steeringWheelPopup == 0) popupText.color = "blue";
    //  if(steeringWheelPopup == 1) popupText.color = "green";
    //  if(steeringWheelPopup == 2) popupText.color = "yellow";
//
    //  animationDuration = 500
    //  popup.visible = true;
    //  popupStatic.start();
    //}
//
    //else if(steeringWheelPopup == 3 || steeringWheelPopup == 4) {
    //  popup.visible = true;
    //  tabView.visible = false;
    //  buttonsClick = false
    //  animationDuration = 2500
    //  popupStatic.start();
    //}
//
    //else {
    //  popup.visible = true;
    //  tabView.visible = false;
    //  buttonsClick = false;
    //}
  }

  ParallelAnimation {
    id: popupStatic
    running: false
    PropertyAnimation {
       target: popup; 
       properties: "visible"; 
       from: true;
       to: false; 
       duration: animationDuration
    }
    PropertyAnimation {
       target: tabView; 
       properties: "visible"; 
       from: false;
       to: true; 
       duration: animationDuration
    }

    //When animation stops, enables the buttons again
    onStopped: {
      buttonsClick = true;
      popupText.color = "lightgrey";
    }
  }

  TabView {
    id: tabView
    anchors.fill: parent
    tabPosition: Qt.BottomEdge
    property var stepIntoTab: false
    visible: true

    Connections {
      target: menu
      onBtnClicked: {
        if (btnID == 4 && buttonsClick) {
          if (!tabView.stepIntoTab) {
            if (tabView.getTab(tabView.currentIndex).children[0].disconnect) {
              tabView.getTab(tabView.currentIndex).children[0].disconnect();
            }

            if (tabView.currentIndex == 0) {
              tabView.currentIndex = 5;
            } else {
              tabView.currentIndex--;
            }

            if (tabView.getTab(tabView.currentIndex).children[0].connect) {
              tabView.getTab(tabView.currentIndex).children[0].connect();
            }
          }
        }
        if (btnID == 5 && buttonsClick) {
          if (!tabView.stepIntoTab) {
            if (tabView.getTab(tabView.currentIndex).children[0].disconnect) {
              tabView.getTab(tabView.currentIndex).children[0].disconnect();
            }

            if (tabView.currentIndex == 5) {
              tabView.currentIndex = 0;
            } else {
              tabView.currentIndex++;
            }

            if (tabView.getTab(tabView.currentIndex).children[0].connect) {
              tabView.getTab(tabView.currentIndex).children[0].connect();
            }
          }
        }
        if (btnID == 0 && !buttonsClick) {
          popupStatic.stop();
          popup.visible = false;
          tabView.visible = true;
          buttonsClick = true;
        }
      }
    }

    Tab {
      TabErrors {
      }
    }
    Tab {
      TabStatus {
      }
    }
    Tab {
      TabSensors {
      }
    }
    Tab {
      TabInverter {
      }
    }
    Tab {
      RacingPage {
      }
    }
    // Tab {
    //   TabBattery {
    //   }
    // }
    // Tab{
    //   TabTelemetry{
    //   }
    // }
    Tab{
      TabTelemedreams{
      }
    }
    
    style: TabViewStyle {
      frameOverlap: 0
      tab: Rectangle {
        color: styleData.selected ? "lightgray" : "black" //#2266FF
        border.color: "lightgray"
        border.width:  0.5
        x: 2
        implicitWidth: tabView.width/6
        implicitHeight:  5
      }
    }
  }

  //This will popup messages over the Tabview
  Rectangle {
    id: popup
    anchors.fill: parent
    color: "transparent"
    visible: false

    Text {
      id: popupText
      anchors.centerIn: parent
      font.family: blackops.name
      font.pointSize: 60
      color: "lightgrey"
    }
  }

}
