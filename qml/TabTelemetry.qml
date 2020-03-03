import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle{
   id: root
   anchors.fill: parent
   color: "#000"

   property var selectedSection: -1 //Current selected section
   property var selectedIndex: -1 //Current selected element into the current section
   property var enabled: [0, 0] //Identify the current Test and Driver
   property var test: 0 //Identify the test section
   property var driver: 1 //Identify the driver section
   property var ntest: 5 //Number of cells into test section
   property var ndriver: 3 //Number of cells into driver section
   property var btnClickable: false //Enable/Disable buttons
   property var dClickable: true //Enable/Disable D button
   property var firstSend: false //Disable onTelemetrystatusChanged the first time
   property var telemetrystatus: CarStatus.TelemetryStatus

   property var testLeds: [ //0 OFFLINE, 1 ONLINE, 2 DEFAULT
      ["Test1", '1'],
      ["Test2", '0'],
      ["Test3", '0'],
      ["Test4", '0'],
      ["Test5", '0'],
   ]

   property var driverLeds: [ //0 OFFLINE, 1 ONLINE, 2 DEFAULT
      ["D1", '1'],
      ["D2", '0'],
      ["D3", '0'],
   ]

   onTelemetrystatusChanged: {
      //Avoid the first update, currently disabled         
      //Rebuild leds
      var newTestStatus = testLeds;
      var newDriverStatus = driverLeds;

      for(var i = 0; i < ntest; i++) {
         newTestStatus[i][1] = 0;
         if(i == telemetrystatus[0]) newTestStatus[i][1] = '1';
      }

      for(var i = 0; i < ndriver; i++) {
         newDriverStatus[i][1] = 0;
         if(i == telemetrystatus[1]) newDriverStatus[i][1] = '1';
      }

      //Update current enabled leds indicator
      enabled[test] = telemetrystatus[0];
      enabled[driver] = telemetrystatus[1];
      //Apply changes
      testLeds = newTestStatus;
      driverLeds = newDriverStatus;
   }

   function connect() {
       menu.btnClicked.connect(btnClickedHandler);
   }

   function disconnect() {
       menu.btnClicked.disconnect(btnClickedHandler);
   }

   function unSelectIndex(type) {
      if(selectedIndex != -1) {
         if(type == test) {
            testRepeater.itemAt(selectedIndex).selected = 0;
         } else {
            driverRepeater.itemAt(selectedIndex).selected = 0;
         }
      }
   }

   function unSelectSection() {
      if(selectedSection == 0) {
         rectTest.selected = 0
      } else {
         rectDriver.selected = 0
      }
   }

   function selectIndex(index, type) {
      unSelectIndex(type);

      if(type == test) {
         if(index < 0) index = ntest - 1;
         index = index % ntest;
         testRepeater.itemAt(index).selected = 1;
      }
      else if(type == driver){
         if(index < 0) index = ndriver - 1;
         index = index % ndriver;
         driverRepeater.itemAt(index).selected = 1;
      } else {
         console.log("Error, type inserted is wrong")
      }

      selectedIndex = index;
   }

   function selectSection(index) {
      unSelectSection();

      index = index % 2;
      if(index == 0) {
         rectTest.selected = 1;
      } else {
         rectDriver.selected = 1;
      }
      selectedSection = index;
   }
   
   function setSelectedIndex(index, type) {
      if(type == test) {
         testRepeater.itemAt(enabled[test]).state = 0;
         testRepeater.itemAt(index).state = 1;
         enabled[test] = index;
         CarStatus.setTest(index);
      } 
      else if(type == driver){
         driverRepeater.itemAt(enabled[driver]).state = 0;
         driverRepeater.itemAt(index).state = 1;
         enabled[driver] = index;
         CarStatus.setDriver(index);
      } 
      else {
         console.log("Error, type inserted is wrong")
      }
   }

   //To do
   function btnClickedHandler(btnID) {
      if (btnID == 0) {
         if (tabView.stepIntoTab) {
            if (selectedIndex != -1) {
               unSelectIndex(selectedSection)
               dClickable = true;
               selectedIndex = -1
            } else {
               mainwindow.canSwitchPage = true;
               tabView.stepIntoTab = false;
               unSelectSection();
               selectedSection = -1
            }
         }
      }
      //Change status of the selected item
      if (btnID == 1) {
         if(tabView.stepIntoTab) {
            
            if(selectedSection != -1) {
               if(selectedIndex != -1) {
                  setSelectedIndex(selectedIndex, selectedSection)
               } else {
                  selectIndex(0, selectedSection)
                  dClickable = false;
               }
            }

         }          
      }           
      
      if (btnID == 2 && dClickable) {
         // Step into this tab and change the behaviour of btnID
         if (!tabView.stepIntoTab) {
            // Set the button clickable
            btnClickable = true;
            // Select the first entry of the SensorsList
            selectSection(0);
            // Prevent the button 0 to switch to Racing Page!
            tabView.stepIntoTab = true;
            mainwindow.canSwitchPage = false;
            console.log("entered in tab")
         } else {
            // Loop through sensors
            selectSection(selectedSection + 1);
         }
      }
      //Enable/Disable sendTelemetry
      if (btnID == 3){
         CAN.asktelemetry();           
      }

      if (btnID == 4 && selectedIndex != -1) {
         selectIndex(selectedIndex - 1, selectedSection);
      }

      if ((btnID == 5 || btnID == 2) && selectedIndex != -1) {
         selectIndex(selectedIndex + 1, selectedSection);
      }

    }

   Rectangle {
      id: rectTest
      color: selected == 1 ? "#222222" : "transparent"
      radius: selected == 1 ? "5" : "0"
      width: parent.width
      height: parent.height * 2 / 3 //2 rows out of three
      anchors.top: parent.top
      
      property var selected: 0

      Grid {
         id: testgrid
         columns: 3
         rows: 2       
         columnSpacing: 2
         rowSpacing: 1
         anchors.centerIn: parent
         width: parent.width - 12
         height: parent.height - 4

         Repeater {
            id: testRepeater
            model: testLeds
            TelemetryStatusLED {
               text: modelData[0]
               state: modelData[1]
               selected: 0
               height: parent.height/2
               width: parent.width/3
            }
         }     
      }
   }

   Rectangle {
      id: separator
      color: "lightgrey"
      width: rectTest.width
      height: 1
      anchors.top: rectTest.bottom
   }

   Rectangle {
      id: rectDriver
      color: selected == 1 ? "#222222" : "transparent"
      radius: selected == 1 ? "5" : "0"
      width: parent.width
      height: parent.height / 3 - 2
      anchors.top: separator.bottom

      property var selected : 0

      Grid {
         id: driverGrid
         columns: 3
         rows: 1
         columnSpacing: 2
         rowSpacing: 1
         anchors.centerIn: parent
         width: parent.width - 12
         height: parent.height - 2

         Repeater {
            id: driverRepeater
            model: driverLeds
            TelemetryStatusLED {
               text: modelData[0]
               state: modelData[1]
               selected: 0
               height: parent.height
               width: parent.width / 3
            }
         }
      }
   }
}