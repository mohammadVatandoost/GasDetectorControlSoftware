import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.VirtualKeyboard 2.2

Page {
    id: root
    property int sensorId: 0
    property string date_time: new Date().toLocaleString(locale, Locale.ShortFormat)
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
            text: qsTr("Sensor "+root.sensorId+"    "+date_time)
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
        onSensorSelect : {
            root.sensorId = sensorId;
            console.log("sensor id :" + sensorId);
            configs.setSensorId(sensorId);
            chartS.setSensorId(sensorId);
            configs.updateConfig();
            comboBoxGas.currentIndex = comboBoxGas.getIndex();
            drawer.close();
        }
    }



   Grid {
       columns: window.width > 767 ? 2 : 1
       width: parent.width
       spacing: 2
       topPadding: 10
       rightPadding: 10
       leftPadding: 10

       ChartComponent {
           id: chartS
           width: window.width > 1023 ? parent.width*2/3 : parent.width/2
       }

     ColumnLayout {
       width: window.width > 1023 ? parent.width/3 : parent.width/2
       Equation {
         id: equation
         Component.onCompleted: {
             console.log("Equation :")
             setVariables(root.sensorId, SensorsList.getEquationType(root.sensorId), SensorsList.getEquationA(root.sensorId),
                          SensorsList.getEquationB(root.sensorId),
                          SensorsList.getEquationC(root.sensorId), SensorsList.getEquationD(root.sensorId), SensorsList.getEquationE(root.sensorId))
             refresh();
         }
         onConfigSelected: {
             equationPopup.open();
         }
       }

       Configs {
           id: configs
           Layout.topMargin: 15
           onConfigSelected: {
               popup.setConfigId(configId)
               popup.setConfigName(configName)
               popup.setConfigValue(configValue)
               popup.open();
           }
       }

      Pane {
           id: pane
           Layout.fillWidth: true

        RowLayout {
           width: parent.width

           ColumnLayout {

               Label {
                   text: "Area"
                   font.pixelSize: 22
               }

               Text {
                   Layout.alignment: Qt.AlignHCenter
                   text: qsTr("DC")
               }
           }

           ColumnLayout {

               Label {
                   text: "In"
                   font.pixelSize: 22
               }

               Text {
                   Layout.alignment: Qt.AlignHCenter
                   text: qsTr("DC")
               }
           }

           ColumnLayout {

               Label {
                   text: "Out"
                   font.pixelSize: 22
               }

               Text {
                   Layout.alignment: Qt.AlignHCenter
                   text: qsTr("DC")
               }
           }

           ComboBox {
               id: comboBoxGas
               property var gasTypes: [ "NO", "CO", "SO2", "O2", "BTEX", "VOC" ]
               function getIndex() {
                   var gasType = SensorsList.getGasTypeValue(root.sensorId)
                   for(var i=0; i< gasTypes.length; i++) {
                       if(gasTypes[i] === gasType) {
                           return i;
                       }
                   }
                   return 0;
               }

               width: 200
               model: gasTypes
               currentIndex: getIndex()
               onActivated:SensorsList.setGasTypeValue(root.sensorId, gasTypes[currentIndex])
           }
       }
      }
      Pane {
           id: pane3
           Layout.fillWidth: true

           RowLayout {
              width: parent.width

              ColumnLayout {

//                  Label {
//                      text: "PPM"
//                      font.pixelSize: 22
//                  }
                  ComboBox {
                      id: comboBoxPressure
                      property var pressureTypes: [ "PPM", "%", "PPB"]
                      function getIndex() {
                          var pressureType = SensorsList.getPressureTypeValue(root.sensorId)
                          for(var i=0; i< pressureTypes.length; i++) {
                              if(pressureTypes[i] === pressureType) {
                                  return i;
                              }
                          }
                          return 0;
                      }

                      width: 200
                      model: pressureTypes
                      currentIndex: getIndex()
                      onActivated:SensorsList.setPressureTypeValue(root.sensorId, pressureTypes[currentIndex])
                  }

                  Text {
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr("0")
                  }
              }

              ColumnLayout {

                  Label {
                      text: "RES"
                      font.pixelSize: 22
                  }

                  Text {
                      id: res
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr(SensorsList.getRes(sensorId) + "")
                  }
              }

              ColumnLayout {

                  Label {
                      text: "TEMP"
                      font.pixelSize: 22
                  }

                  Text {
                      id: temp
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr(SensorsList.getCurrent(sensorId))
                  }
              }

          }
      }

      Pane {
           id: pane1
           Layout.fillWidth: true
           RowLayout {
               Button {
                   id: pump
                   property bool onOff: false
                   text: qsTr("Pump")
                   highlighted: true
                   Material.background: Material.red
                   onClicked: {
                       if(onOff) {
                           onOff = false;
                           pump.Material.background =  Material.red
                       } else {
                           onOff = true;
                           pump.Material.background =  Material.Green
                       }
                   }
               }

               Button {
                   id: rec
                   property bool onOff: false
                   text: qsTr("Rec")
                   highlighted: true
                   Material.background: Material.red
                   onClicked: {
                       if(onOff) {
                           onOff = false;
                           rec.Material.background =  Material.red
                       } else {
                           onOff = true;
                           heaterStart.onOff = false;
                           rec.Material.background =  Material.Green
                           heaterStart.Material.background =  Material.red
                           BackEnd.sendSensorDataRec(root.sensorId)
                       }
                   }
               }

               Button {
                   id: heaterStart
                   property bool onOff: false
                   text: qsTr("Heater Start")
                   highlighted: true
                   Material.background: Material.red
                   onClicked: {
                       if(onOff) {
                           onOff = false;
                           heaterStart.Material.background =  Material.red
                       } else {
                           onOff = true;
                           rec.onOff = false;
                           heaterStart.Material.background =  Material.Green
                           rec.Material.background =  Material.red
                           BackEnd.sendSensorDataHeater(root.sensorId)
                       }
                   }
               }

           }
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

   EquationInsert {
       id: equationPopup
       Component.onCompleted: {
           setVariables(root.sensorId, SensorsList.getEquationType(root.sensorId), SensorsList.getEquationA(root.sensorId), SensorsList.getEquationB(root.sensorId),
                        SensorsList.getEquationC(root.sensorId), SensorsList.getEquationD(root.sensorId), SensorsList.getEquationE(root.sensorId))
//           setPowers(SensorsList.getEquationPowers(sensorId))
//           setCoefficients(SensorsList.getEquationCoefficient(sensorId))
//           refresh()
       }
       onUpdated: {
           console.log("upated id:"+root.sensorId)
           console.log(SensorsList.getEquationType(root.sensorId)+","+SensorsList.getEquationA(root.sensorId))
           console.log(SensorsList.getEquationB(root.sensorId)+","+SensorsList.getEquationC(root.sensorId))
           console.log(SensorsList.getEquationD(root.sensorId)+","+SensorsList.getEquationE(root.sensorId))
           equation.setVariables(root.sensorId, SensorsList.getEquationType(root.sensorId), SensorsList.getEquationA(root.sensorId),
                        SensorsList.getEquationB(root.sensorId),
                        SensorsList.getEquationC(root.sensorId), SensorsList.getEquationD(root.sensorId), SensorsList.getEquationE(root.sensorId))
           equation.refresh();
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
               res.text = SensorsList.getRes(sensorId).toFixed(2) ;
               temp.text = SensorsList.getTemp(sensorId).toFixed(2);
//               console.log("trigerred "+sensorId);
//               console.log(SensorsList.getTemp(sensorId) );
//               console.log(SensorsList.getRes(sensorId) );
           }
    }
}
