import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

Page {
    id: root

    ScrollView
    {
        id: scrollView
        anchors.fill: parent
        Component.onCompleted: {
            console.log("root.StackView.view");
            console.log(root.StackView);
        }
      RowLayout {
        ColumnLayout {
          RowLayout {
            ColumnLayout {
                RowLayout {
                    Image {
                        sourceSize.width: 60
                        sourceSize.height: 60
                        source: "images/blackTemp.jpeg"
                    }
                    Text {
                        id: temp1
                        text: qsTr("temp1")
                    }
                }
                RowLayout {
                    Image {
                        sourceSize.width: 60
                        sourceSize.height: 60
                        source: "images/greenTemp.png"
                    }
                    Text {
                        id: temp2
                        text: qsTr("temp2")
                    }
                }
            }
            ColumnLayout {
                RowLayout {
                    Image {
                        sourceSize.width: 60
                        sourceSize.height: 60
                        source: "images/heaterBlack.png"
                    }
                    Text {
                        id: h1
                        text: qsTr("H1")
                    }
                }
                RowLayout {
                    Image {
                        sourceSize.width: 60
                        sourceSize.height: 60
                        source: "images/heaterRed.png"
                    }
                    Text {
                        id: h2
                        text: qsTr("H2")
                    }
                }
            }
          }
          Image {
              sourceSize.width: 100
              sourceSize.height: 100
              anchors.horizontalCenter: parent.horizontalCenter
              source: "images/pumpBlack.png"
          }
          RowLayout {
              spacing: 6
              ColumnLayout {
                  Label {
                      text: "Area"
                      font.pixelSize: 22
                  }
                  Text {
                      anchors.horizontalCenter: parent.Center
                      text: qsTr("DC")
                  }
              }
              ColumnLayout {
                  Label {
                      text: "In"
                      font.pixelSize: 22
                  }
                  Text {
                      anchors.horizontalCenter: parent.Center
                      text: qsTr("DC")
                  }
              }
              ColumnLayout {
                  Label {
                      text: "Out"
                      font.pixelSize: 22
                  }
                  Text {
                      anchors.horizontalCenter: parent.Center
                      text: qsTr("DC")
                  }
              }
          }
        }

        ColumnLayout {
           anchors.top: parent.top
           RowLayout {
               Text {
                   text: qsTr("NO")
               }
               ProgressBar {
                   value: 0.5
               }
               Text {
                   text: qsTr("DC")
               }
               StatusIndicator {
                       color: "green"
                       active: true
               }
           }
           Button {
//               anchors.horizontalCenter: parent.Center
               text: qsTr("Start")
               highlighted: true
               Material.background: Material.Teal
           }
           Button {
//               anchors.horizontalCenter: parent.Center
               text: qsTr("Login")
               highlighted: true
               Material.background: Material.Green
               onClicked: root.StackView.view.push("qrc:/Login.qml")
           }

        }
      }
    }
}
