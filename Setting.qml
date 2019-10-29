import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Page {
    id: root
    property int sensorId: 1
    header: ToolBar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: "Sensor 1"
            font.pixelSize: 20
            anchors.centerIn: parent
        }

        ToolButton {
            text: qsTr("Menu")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: drawer.open()
        }
    }

    NavigationDrawer {
        id: drawer
        onSensorSelect : {root.sensorId = sensorId; console.log("sensor id :" + sensorId);drawer.close();}
    }


   Grid {
       anchors.top: rectanglePadding.bottom
       columns: window.width > 767 ? 2 : 1
       spacing: 2
       topPadding: 10
       rightPadding: 10
       leftPadding: 10

       Configs {
           id: configs
           onConfigSelected: {
               popup.setConfigId(configId)
               popup.setConfigName(configName)
               popup.setConfigValue(configValue)
               popup.open();
           }
       }
   }

   Popup {
           id: popup
           padding: 10
           width: 400
           height: 300
           x: Math.round((parent.width - width) / 2)
           y: Math.round((parent.height - height) / 2)
           modal: true
           focus: true
           closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

           property int configId
           property string configName: "test"
           property string configValue: "test"

           function setConfigId(temp) {configId = temp;}
           function setConfigName(temp) {configName = temp;}
           function setConfigValue(temp) {configValue = temp;}
           signal configSet(int configId, string configName, string configValue)

           ColumnLayout {
               anchors.fill: parent

               Label {
                   text: qsTr(popup.configName)
                   font.pixelSize: 20
                   font.bold: true
                   Layout.topMargin: 40
                   Layout.bottomMargin: 20
                   Layout.alignment: Qt.AlignHCenter
               }
               TextEdit {
                   id: configTextEdit
                   text: qsTr(popup.configValue)
                   height: 40
                   width: 100
                   font.pixelSize: 18
                   Layout.alignment: Qt.AlignHCenter
               }
               Rectangle {
                   anchors.top: configTextEdit.bottom
                   width: parent.width
                   height: 60
               }

               Pane {
                   id: pane
                   Layout.fillWidth: true

                  RowLayout {
                     width: parent.width
                     Layout.alignment: Qt.AlignJustify
                     Button {
                         text: qsTr("Cancel")
                         highlighted: true
                         Material.background: Material.Red
                         onClicked: popup.close()
                         Layout.alignment: Qt.AlignHCenter
                     }
                     Button {
                         text: qsTr("Submit")
                         highlighted: true
                         Material.background: Material.Green
                         onClicked: {
                             console.log("submited :"+configTextEdit.text);
                             if(popup.configId === 1) {
                               SensorsList.setFilterValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 2) {
                                 SensorsList.setR0Value(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 3) {
                                 SensorsList.setRThValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 4) {
                                 BackEnd.setPumpValue(configTextEdit.text);
                             } else if(popup.configId === 5) {
                                 SensorsList.setTempValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 6) {
                                 SensorsList.setNameValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 7) {
                                 SensorsList.setRecTimeValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 8) {
                                 SensorsList.setRecTempValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 9) {
                                 SensorsList.setOPTimeValue(root.sensorId, configTextEdit.text);
                             }

                             configs.setConfigVaue(popup.configId, configTextEdit.text);
                             popup.close();
                         }
                         Layout.alignment: Qt.AlignHCenter
                     }

                 }

               }

           }
    }

}
