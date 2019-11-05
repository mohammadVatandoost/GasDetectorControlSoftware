import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import SensorModel 1.0

Page {
    id: root
    property string date_time: new Date().toLocaleString(locale, Locale.ShortFormat)

    ColumnLayout {
        anchors.fill: parent

        Text {
            id: time
            text: qsTr(root.date_time)
            font.pixelSize: 22
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 5
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 5

            clip: true
            id: listView
            spacing: 10
            model: SensorModel {
                list: SensorsList
            }

            delegate: SensorInfo {
                Component.onCompleted: {
                    setTemp(model.tempActive);
                    setHeater(model.heaterActive);
                    setSensorActive(model.sensorActive);
                    setSensorName(model.gasType);
                    setProgressValue(0);
                    setSensorId(index+1)
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true
            property bool pumpActive: false
            property string humidityIn: "DC"
            property string humidityOut: "DC"
            property string humidityArea: "DC"
            property string tempArea: "DC"
            property string presueArea: "DC"

            function refreshData() {
                console.log("refreshData");
                pumpActive = BackEnd.getPumpStatus();
                humidityIn = BackEnd.getHumidityIn();
                humidityOut = BackEnd.getHumidityOut();
                humidityArea = BackEnd.getHumidityArea();
                tempArea = BackEnd.getTempArea()
                presueArea = BackEnd.getTempArea()
            }

         RowLayout {
             width: parent.width

             ColumnLayout {

                 Label {
                     text: "PresureArea"
                     font.pixelSize: 22
                 }

                 Text {
                     Layout.alignment: Qt.AlignHCenter
                     text: qsTr(pane.presueArea)
                 }
             }

             ColumnLayout {

                 Label {
                     text: "TempArea"
                     font.pixelSize: 22
                 }

                 Text {
                     Layout.alignment: Qt.AlignHCenter
                     text: qsTr(pane.tempArea)
                 }
             }

             ColumnLayout {

                 Label {
                     text: "Area"
                     font.pixelSize: 22
                 }

                 Text {
 //                    id: humidityArea
                     Layout.alignment: Qt.AlignHCenter
                     text: qsTr(pane.humidityArea)
                 }
             }

             ColumnLayout {

                 Label {
                     text: "In"
                     font.pixelSize: 22
                 }

                 Text {
 //                    id: humidityIn
                     Layout.alignment: Qt.AlignHCenter
                     text: qsTr(pane.humidityIn)
                 }
             }
             ColumnLayout {

                 Label {
                     text: "Out"
                     font.pixelSize: 22
                 }

                 Text {
 //                    id: humidityOut
                     Layout.alignment: Qt.AlignHCenter
                     text: qsTr(pane.humidityOut)
                 }
             }
         }

          RowLayout {
              width: parent.width

            ColumnLayout {
                Label {
                   Layout.alignment: Qt.AlignHCenter
                   text: "Pump"
                   font.pixelSize: 22
                }
                Image {
                  sourceSize.width: 100
                  sourceSize.height: 100
                  source: pane.pumpActive ? "images/pumpBlue.jpeg" : "images/pumpBlack.png"
                }
            }     

            Button {
                text: qsTr("Start")
                highlighted: true
                Material.background: Material.Teal
                onClicked: BackEnd.startAllSensor()
            }

            Button {
                text: qsTr("Login")
                highlighted: true
                Material.background: Material.Green
                onClicked: root.StackView.view.push("qrc:/Login.qml")
            }

          }

        }

    }

    Timer {
            interval: 45000; running: true; repeat: true
            onTriggered: {
                root.date_time = new Date().toLocaleString(locale, Locale.ShortFormat)
            }
     }
}
