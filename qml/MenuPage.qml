import Const 1.0
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import "tabs"

Item {
    id: menu

    property var buttonsClick: true

    signal btnPressed(int btnID)
    signal btnReleased(int btnID)
    signal btnClicked(int btnID)

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
        if (currentTab && currentTab.children[0].disconnect)
            currentTab.children[0].disconnect();

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

    TabView {
        id: tabView

        property var stepIntoTab: false

        anchors.fill: parent
        tabPosition: Qt.BottomEdge
        visible: true

        Connections {
            function onBtnClicked(btnID) {
                if (btnID === 4 && buttonsClick) {
                    if (!tabView.stepIntoTab) {
                        if (tabView.getTab(tabView.currentIndex).children[0].disconnect)
                            tabView.getTab(tabView.currentIndex).children[0].disconnect();

                        if (tabView.currentIndex === 0)
                            tabView.currentIndex = tabView.count - 1;
                        else
                            tabView.currentIndex--;
                        if (tabView.getTab(tabView.currentIndex).children[0].connect)
                            tabView.getTab(tabView.currentIndex).children[0].connect();

                    }
                }
                if (btnID === 5 && buttonsClick) {
                    if (!tabView.stepIntoTab) {
                        if (tabView.getTab(tabView.currentIndex).children[0].disconnect)
                            tabView.getTab(tabView.currentIndex).children[0].disconnect();

                        if (tabView.currentIndex === tabView.count - 1)
                            tabView.currentIndex = 0;
                        else
                            tabView.currentIndex++;
                        if (tabView.getTab(tabView.currentIndex).children[0].connect)
                            tabView.getTab(tabView.currentIndex).children[0].connect();

                    }
                }
                if (btnID === 0 && !buttonsClick) {
                    popupStatic.stop();
                    popup.visible = false;
                    tabView.visible = true;
                    buttonsClick = true;
                }
            }

            target: menu
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
            TabRacing {
            }

        }

        Tab {
            TabTelemedreams {
            }

        }

        Tab {
            TabGps {
            }

        }

        style: TabViewStyle {
            frameOverlap: 0

            frame: Rectangle {
                color: Style.background
            }

            tab: Rectangle {
            }

        }

    }

    Rectangle {
        width: animation.width
        height: animation.height
        visible: false

        AnimatedImage {
            id: animation

            source: "img/loading/loading.gif"
        }

    }

}
