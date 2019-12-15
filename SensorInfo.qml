import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
    id: root
    width: parent.width

    property bool tempActive: false
    property bool heaterActive: false
    property bool sensorActive: false
    property string sensorName: ""
    property string sensorPressure: "DC"
    property double progressValue: 0
    property int sensorId: 1

    function setTemp(temp) { tempActive = temp;}
    function setHeater(temp) { heaterActive = temp;}
    function setSensorActive(temp) { sensorActive = temp;}
    function setProgressValue(temp) { progressValue = temp;}
    function setSensorName(temp) { sensorName = temp;}
    function setSensorId(temp) {sensorId = temp;}
    function setSensorPressure(temp) {
        sensorPressure = temp; presureValue.text = temp;
    }

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
        id: control
        value: progressValue
        padding: 2

        background: Rectangle {
            implicitWidth: 300
            implicitHeight: 15
            color: "#e6e6e6"
            radius: 3
        }

        contentItem: Item {
            implicitWidth: 300
            implicitHeight: 4

            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                radius: 2
                color: "#17a81a"
            }
        }
    }
    Text {
        id: presureValue
        text: qsTr(root.sensorPressure)
    }
    StatusIndicator {
            color: "green"
            active: sensorActive
    }
    Button {
        text: alghoritmRunning ? qsTr("Stop") : qsTr("Start")
        highlighted: true
        Material.background: alghoritmRunning ? Material.Light : Material.Teal
        onClicked: BackEnd.startSensor(sensorId)
    }
}
