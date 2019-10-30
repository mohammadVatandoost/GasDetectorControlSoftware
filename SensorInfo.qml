import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
    property bool tempActive: false
    property bool heaterActive: false
    property bool sensorActive: false
    property string sensorName: ""
    property double progressValue: 0

    function setTemp(temp) { tempActive = temp;}
    function setHeater(temp) { heaterActive = temp;}
    function setSensorActive(temp) { sensorActive = temp;}
    function setProgressValue(temp) { progressValue = temp;}
    function setSensorName(temp) { sensorName = temp;}

    Image {
        sourceSize.width: 60
        sourceSize.height: 60
        source: tempActive ?  "images/greenTemp.png" : "images/blackTemp.jpeg"
    }
    Text {
        id: temp1
        text: qsTr("temp")
    }
    Image {
        sourceSize.width: 60
        sourceSize.height: 60
        source: heaterActive ?  "images/heaterRed.png" : "images/heaterBlack.png"
    }
    Text {
        id: h1
        text: qsTr("H")
    }
    Text {
        text: qsTr(sensorName)
    }
    ProgressBar {
        value: progressValue
    }
    Text {
        text: qsTr("DC")
    }
    StatusIndicator {
            color: "green"
            active: sensorActive
    }
}
