import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.FreeVirtualKeyboard 1.0
//import QtQuick.VirtualKeyboard 2.1

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
            text: "Brooks"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
    ColumnLayout {
        anchors.fill: parent
    ListView {
        Layout.fillWidth: true
//        width: 800
        Layout.fillHeight: true
        Layout.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        clip: true
        id: listView
        spacing: 10
//      columns: 2
//      width: parent.width

//      spacing: 2
      model: BrooksChannelModel
      delegate: ChannelItem {
            gasType: model.name
            spRateReaded: model.rateReaded
            spRate: model.spRate
            channelId: index
            vor: model.VOR
          Component.onCompleted: {

          }
          onChannelSelected: {
              popup.setChannelId(channelId);
              popup.setSpRateValue(spRate);
              popup.open();
          }

      }
//        ChannelItem {
//           onChannelSelected: {
//               popup.setChannelId(channelId);
//               popup.setSpRateValue(spRate);
//               popup.open();
//           }
//        }
//        ChannelItem {
//            onChannelSelected: {
//                popup.setChannelId(channelId);
//                popup.setSpRateValue(spRate);
//                popup.open();
//            }
//        }
//        ChannelItem {
//            onChannelSelected: {
//                popup.setChannelId(channelId);
//                popup.setSpRateValue(spRate);
//                popup.open();
//            }
//        }
       }
    }


    Popup {
            id: popup
            padding: 0
            width: 400
            height: 150
            x: Math.round((parent.width - width) / 2)
 //           y: Math.round((parent.height - height) / 2)
            y: 40
            z: 10
 //           modal: true
            focus: true
 //           closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
            closePolicy: Popup.CloseOnEscape
            property int channelId
            property double spRateValue: 25.02

            function setChannelId(temp) {channelId = temp;}
            function setSpRateValue(temp) {spRateValue = temp;}
//            signal spRateSet(int configId, string configName, string configValue)

            ColumnLayout {
                anchors.fill: parent

                Label {
                    text: qsTr("Sp Rate :")
                    font.pixelSize: 20
                    font.bold: true
                    Layout.bottomMargin: 20
                    Layout.alignment: Qt.AlignHCenter
                }

                TextFieldWithBorder {
                    id: configTextEdit
                    text: qsTr(popup.spRateValue+"")
                    implicitWidth: 100
                    height: 50
                    font.pixelSize: 22
                    Layout.alignment: Qt.AlignHCenter
                    horizontalAlignment: TextInput.AlignHCenter
                }

                Pane {
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
                              BackEnd.setChannelSPRate(popup.channelId, parseFloat(configTextEdit.text));
                              popup.close();
                          }
                          Layout.alignment: Qt.AlignHCenter
                      }

                  }

                }

            }
     }

}
