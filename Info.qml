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
    property bool pumpActive: false
    property string humidityIn: "DC"
    property string humidityOut: "DC"
    property string humidityArea: "DC"
    property string tempArea: "DC"
    property string presueArea: "DC"
    property string batteryCharge: "50%"
    property bool flowError: false
    property bool electricalError: false
    property bool charging: false
    property bool startAll: false

    function refreshData() {
//        console.log("refreshData");
        root.pumpActive = BackEnd.getPumpStatus();
        root.humidityIn = BackEnd.getHumidityIn();
        root.humidityOut = BackEnd.getHumidityOut();
        root.humidityArea = BackEnd.getHumidityArea();
        root.tempArea = BackEnd.getTempArea()
        root.presueArea = BackEnd.getTempArea()
        root.flowError = BackEnd.getFlowErrorStatus()
        root.electricalError = BackEnd.getElectricalErrorStatus()
        root.batteryCharge = BackEnd.getBatteryCharge()
        root.charging = BackEnd.getChargingStatus()
    }

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
                    setProgressValue(model.progressValue);
                    setSensorId(index);
                    setSensorPressure(model.pressure);
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true

            RowLayout {
                width: parent.width

                ColumnLayout {

                    Label {
                        text: "PresureArea"
                        font.pixelSize: 22
                    }

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr(root.presueArea)
                    }
                }

                ColumnLayout {

                    Label {
                        text: "TempArea"
                        font.pixelSize: 22
                    }

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr(root.tempArea)
                    }
                }

                ColumnLayout {

                    Label {
                        text: "Area"
                        font.pixelSize: 22
                    }

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr(root.humidityArea)
                    }
                }

                ColumnLayout {
                    Label {
                        text: "Battery Charge"
                        font.pixelSize: 22
                    }

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr(root.batteryCharge)
                    }
                }

                ColumnLayout {
                    Label {
                        text: "In"
                        font.pixelSize: 22
                    }

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr(root.humidityIn)
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
                        text: qsTr(root.humidityOut)
                    }
                }
            }

        }

        Pane {
            id: pane2
            Layout.fillWidth: true


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
                  source: root.pumpActive ? "images/pumpBlue.jpeg" : "images/pumpBlack.png"
                }
            }
            ColumnLayout {
                Label {
                   Layout.alignment: Qt.AlignHCenter
                   text: "Flow Error"
                   font.pixelSize: 22
                }
                StatusIndicator {
                    Layout.alignment: Qt.AlignHCenter
                    color: "red"
                    active: root.flowError
                }
            }
            ColumnLayout {
                Label {
                   Layout.alignment: Qt.AlignHCenter
                   text: "Electrical Error"
                   font.pixelSize: 22
                }
                StatusIndicator {
                    Layout.alignment: Qt.AlignHCenter
                    color: "red"
                    active: root.electricalError
                }
            }
            ColumnLayout {
                Label {
                   Layout.alignment: Qt.AlignHCenter
                   text: "Charging"
                   font.pixelSize: 22
                }
                StatusIndicator {
                    Layout.alignment: Qt.AlignHCenter
                    color: "green"
                    active: root.charging
                }
            }

            Button {
                text: root.startAll ? qsTr("Stop") : qsTr("Start")
                highlighted: true
                Material.background: root.startAll ? Material.Light : Material.Teal
                onClicked: {
                    root.startAll = !root.startAll;
                    BackEnd.startAllSensor(root.startAll);
                }
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
    Timer {
            interval: 1000; running: true; repeat: true
            onTriggered: {
                root.refreshData();
            }
     }
}
