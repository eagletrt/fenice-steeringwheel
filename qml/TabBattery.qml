import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "#000000"
    FontLoader {id:blackops; source: "../lib/blops.ttf"}

    property var statusHV: [
        ["T Max", "0", "° C"],
        ["T Avg", "0", "° C"],
        ["T Min", "0", "° C"],
        ["V Max", "0", "V"],
        ["V Avg", "0", "V"],
        ["V Min", "0", "V"]
    ]

    property var statusLV: [
        ["V1", "0", "V"],
        ["V2", "0", "V"],
        ["V3", "0", "V"],
        ["V4", "0", "V"],
        ["V5", "0", "V"],
        ["Tot E", "0", "J"]
    ]

	function connect() {
        // console.log("Tab connessa - Errors");
        mainwindow.btnClicked.connect(btnClickedHandler);
    }

    function disconnect() {
        // console.log("Tab disconnessa - Errors");
        mainwindow.btnClicked.disconnect(btnClickedHandler);
    }

    function btnClickedHandler(btnID) {
        if (btnID == 3){
            CAN.sendMarker();
        }
    }

    GridLayout {
        anchors.fill: parent
        rows: 2
        columns: 1
        rowSpacing: 0
        columnSpacing: 0

        Rectangle {
            height: 30
            Layout.fillWidth: true
            color: "red"

            GridLayout {
                anchors.fill: parent
                columns: 2
                rows: 1
                rowSpacing: 0
                columnSpacing: 0

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    border.color: "black"
                    border.width: 4
                    color: "green"

                    Text {
                        text: "HV"
                        font.family: blackops.name;
                        font.pointSize: 30
                        anchors.centerIn: parent
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    border.color: "black"
                    border.width: 4
                    color: "blue"

                    Text {
                        font.family: blackops.name;
                        font.pointSize: 30
                        text: "LV"
                        anchors.centerIn: parent
                    }
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "red"

            GridLayout {
                anchors.fill: parent
                columns: 2
                rows: 1
                rowSpacing: 0
                columnSpacing: 0

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "black"

                    GridLayout {
                        anchors.fill: parent
                        /*
                        HVBatteryCharge {
                            width: root.width / 6
                            Layout.fillHeight: true
                            charge: 10
                        }
                        */
                        Rectangle {
                            color: "transparent"
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Column {
                                id: col
                                spacing: 0
                                anchors.fill: parent

                                Repeater {
                                    model: statusHV
                                    Rectangle {
                                        width: col.width
                                        height: col.height / 6
                                        color: "transparent"

                                        Text {
                                            anchors.centerIn: parent
                                            font.family: blackops.name;
                                            font.pointSize: 18
                                            text: modelData[0] + ":" + modelData[1] + " " + modelData[2]
                                            color: "lightgray"
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "black"

                    GridLayout {
                        anchors.fill: parent


                        Rectangle {
                            color: "transparent"
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Column {
                                id: col2
                                spacing: 0
                                anchors.fill: parent

                                Repeater {
                                    model: statusLV
                                    Rectangle {
                                        width: col2.width
                                        height: col2.height / 6
                                        color: "transparent"

                                        Text {
                                            anchors.centerIn: parent
                                            font.family: blackops.name;
                                            font.pointSize: 18
                                            text: modelData[0] + ":" + modelData[1] + " " + modelData[2]
                                            color: "lightgray"
                                        }
                                    }
                                }
                            }
                        }
                        /*
                        HVBatteryCharge {
                            width: root.width / 6
                            Layout.fillHeight: true
                            charge: 5
                        }
                        */
                    }
                }
            }
        }
    }

}
