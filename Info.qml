import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import SensorModel 1.0

Page {
    id: root


    ColumnLayout {
        anchors.fill: parent

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
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
                    setProgressValue(0);
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            anchors.top: listView.bottom
            Layout.fillWidth: true
          RowLayout {
              width: parent.width
//            Layout.topMargin: listView.width
//            anchors.top: listView.bottom
            Image {
                sourceSize.width: 100
                sourceSize.height: 100
//                anchors.horizontalCenter: parent.horizontalCenter
                source: "images/pumpBlack.png"
            }
            ColumnLayout {
                Label {
                    text: "Area"
                    font.pixelSize: 22
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("DC")
                }
            }
            ColumnLayout {
                Label {
                    text: "In"
                    font.pixelSize: 22
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("DC")
                }
            }
            ColumnLayout {
                Label {
                    text: "Out"
                    font.pixelSize: 22
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("DC")
                }
            }
            Button {
//                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Start")
                highlighted: true
                Material.background: Material.Teal
            }
            Button {
//                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Login")
                highlighted: true
                Material.background: Material.Green
                onClicked: root.StackView.view.push("qrc:/Login.qml")
            }
          }
        }

//      RowLayout {
//        ColumnLayout {
//          RowLayout {
//            ColumnLayout {

//                RowLayout {
//                    Image {
//                        sourceSize.width: 60
//                        sourceSize.height: 60
//                        source: "images/greenTemp.png"
//                    }
//                    Text {
//                        id: temp2
//                        text: qsTr("temp2")
//                    }
//                }
//            }
//            ColumnLayout {
//                RowLayout {
//                    Image {
//                        sourceSize.width: 60
//                        sourceSize.height: 60
//                        source: "images/heaterBlack.png"
//                    }
//                    Text {
//                        id: h1
//                        text: qsTr("H1")
//                    }
//                }
//                RowLayout {
//                    Image {
//                        sourceSize.width: 60
//                        sourceSize.height: 60
//                        source: "images/heaterRed.png"
//                    }
//                    Text {
//                        id: h2
//                        text: qsTr("H2")
//                    }
//                }
//            }
//          }

//          RowLayout {
//              spacing: 6

//          }
//        }

//        ColumnLayout {
//           anchors.top: parent.top
//           RowLayout {
//               Text {
//                   text: qsTr("NO")
//               }
//               ProgressBar {
//                   value: 0.5
//               }
//               Text {
//                   text: qsTr("DC")
//               }
//               StatusIndicator {
//                       color: "green"
//                       active: true
//               }
//           }


//        }
//      }
    }
}
