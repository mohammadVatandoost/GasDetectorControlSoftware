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
        source: root.tempActive ?  "images/greenTemp.png" : "images/blackTemp.jpeg"
    }
    Text {
        id: temp1
        text: qsTr("temp")
    }
    Image {
        sourceSize.width: 60
        sourceSize.height: 60
        source: root.heaterActive ?  "images/heaterRed.png" : "images/heaterBlack.png"
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
        value: root.progressValue
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
            active: root.sensorActive
    }
    Button {
        text: root.alghoritmRunning ? qsTr("Stop") : qsTr("Start")
        highlighted: true
        Material.background: root.alghoritmRunning ? Material.Light : Material.Teal
        onClicked: BackEnd.startSensor(sensorId)
    }

    Timer {
            interval: 1000; running: true; repeat: true
            onTriggered: {
                if(SensorsList.getTempActiveValue(root.sensorId) === 1) {
                    root.tempActive = true ;
                } else { root.tempActive = false ; }
                if(SensorsList.getHeaterActiveValue(root.sensorId) === 1) {
                    root.heaterActive = true ;
                } else { root.heaterActive = false ; }
                if(SensorsList.getSensorActiveValue(root.sensorId) === 1) {
                    root.sensorActive = true ;
                } else { root.sensorActive = false ; }
                if(SensorsList.getAlgorithmRunnigValue(root.sensorId) === 1) {
                    root.alghoritmRunning = true ;
                } else { root.alghoritmRunning = false ; }

                root.sensorPressure = SensorsList.getSensorPressureValue(root.sensorId);
            }
     }
}
