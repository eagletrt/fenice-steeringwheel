import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    color: "transparent"
    property var warning : CarStatus.getWarning;
    property int warningVal : warning;
    property var error : CarStatus.error;
    property int errorVal : error;

   onWarningChanged: {
      warningVal = CarStatus.varWarning;
      if(warningVal == 1)
          warnLED.state = 'on';
      else
          warnLED.state = 'off';
   }
   onErrorChanged: {
      errorVal = CarStatus.error;
      if(errorVal == 1)
          errLED.state = 'on';
      else
          errLED.state = 'off';
   }

    GridLayout {
        anchors.fill: parent
        columns: 4

        CtrlLabelLED {
            id: ctrlLED
            Layout.columnSpan: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
            active: false
        }

        LabelLED {
            id: warnLED
            Layout.fillWidth: true
            Layout.fillHeight: true
            ledColor: "yellow"
            text: "WARN"
            state: "off"
        }

        LabelLED {
            id: errLED
            Layout.fillWidth: true
            Layout.fillHeight: true
            ledColor: "red"
            text: "ERR"
            state: "off"
        }
    }
}
