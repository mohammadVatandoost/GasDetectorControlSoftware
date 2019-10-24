import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Item {
    id: root
    ScrollView
    {
        id: scrollView
        anchors.fill: parent
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
              anchors.horizontalCenter: center
              source: "images/pumpBlack.png"
          }
        }
    }
}
