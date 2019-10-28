import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Page {
    id: root
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
        onSensorSelect : {console.log("sensor id :" + sensorId);drawer.close();}
    }

//   Rectangle {
//       id: rectanglePadding
//       width: parent.width
//       height: 10
//   }

   Grid {
       anchors.top: rectanglePadding.bottom
       columns: window.width > 767 ? 2 : 1
       spacing: 2
       topPadding: 10
       rightPadding: 10
       leftPadding: 10

       Configs {
           onConfigSelected: {
               popup.open();
           }
       }
   }

   Popup {
           id: popup
           x: 100
           y: 100
           padding: 10
           width: 400
           height: 300
           modal: true
           focus: true
           closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

           property int configId
           property string configName
           property string configValue

           function setConfigId(temp) {configId = temp;}
           function setConfigName(temp) {configName = temp;}
           function setConfigValue(temp) {configValue = temp;}
           signal configSet(int configId, string configName, string configValue)

           ColumnLayout {
               Label {
                   text: configName
                   font.pixelSize: 20
                   font.bold: true
                   anchors.horizontalCenter: parent.horizontalCenter
               }
               TextEdit {
                   id: configTextEdit
                   text: configValue
               }

               Pane {
                   id: pane
                   anchors.top: listView.bottom
                   Layout.fillWidth: true
                 RowLayout {
                     width: parent.width
                     Button {
                         text: qsTr("Cancel")
                         highlighted: true
                         Material.background: Material.Red
                         onClicked: popup.close()
                     }
                     Button {
                         text: qsTr("Submit")
                         highlighted: true
                         Material.background: Material.Green
                         onClicked: {console.log("submited :"+configTextEdit.text);}
                     }

                 }
               }

           }
    }

}
