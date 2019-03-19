import QtQuick 2.7

Rectangle {
    id: root

    radius: this.width

    property int index
    property int currentIndex

    color: "transparent"
    //border.color: 'lightgray'

    onCurrentIndexChanged: {
        if (currentIndex == root.index) {
            root.state = 'active'
        } else {
            root.state = 'notactive'
        }
    }

    states: [
        State {
            name: 'active'
            PropertyChanges {
                target: root
                color: 'lightgray'
            }
            PropertyChanges {
                target: text
                color: 'black'
            }
        },
        State {
          name: 'notactive'
          PropertyChanges {
               target: root
               color: 'black'
          }
          PropertyChanges {
               target: text
               color: 'lightgray'
          }
      }
    ]

    Text {
        id: text
        text: root.index //"P" + root.index
        anchors.centerIn: parent
        font.family: blackops.name;
        font.pointSize: 6
        color: "lightgray"
    }
}
