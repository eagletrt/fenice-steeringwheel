import QtQuick 2.7

Rectangle {
    // border.color: 'lightgray'

    id: root

    property int index
    property int currentIndex

    radius: this.width
    color: "transparent"
    onCurrentIndexChanged: {
        if (currentIndex === root.index)
            root.state = 'active';
        else
            root.state = 'notactive';
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
        font.family: labelFont.name
        font.pointSize: 6
        color: "lightgray"
    }

}
