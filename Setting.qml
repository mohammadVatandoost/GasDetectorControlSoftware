import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
//import QtQuick.VirtualKeyboard 2.2

Page {
    id: root
    property int sensorId: 0
    property string date_time: new Date().toLocaleString(locale, Locale.ShortFormat)
    property bool sensorActive: false
    property bool flowError: false
    property bool electricalError: false
    property bool charging: false
    property string humidityIn: "DC"
    property string humidityOut: "DC"
    property string humidityArea: "DC"
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
            text: qsTr("Sensor "+(root.sensorId+1)+"    "+date_time)
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
            console.log("NavigationDrawer sensor id :" + sensorId);
            configs.setSensorId(root.sensorId);
            chartS.setSensorId(root.sensorId);
            configs.updateConfig();
            comboBoxGas.currentIndex = comboBoxGas.getIndex();
            equation.setVariables(root.sensorId, SensorsList.getEquationType(root.sensorId), SensorsList.getEquationA(root.sensorId),
                         SensorsList.getEquationB(root.sensorId),
                         SensorsList.getEquationC(root.sensorId), SensorsList.getEquationD(root.sensorId), SensorsList.getEquationE(root.sensorId))
            equation.refresh();
            equationPopup.setVariables(root.sensorId, SensorsList.getEquationType(root.sensorId), SensorsList.getEquationA(root.sensorId), SensorsList.getEquationB(root.sensorId),
                                       SensorsList.getEquationC(root.sensorId), SensorsList.getEquationD(root.sensorId), SensorsList.getEquationE(root.sensorId));
            drawer.close();
        }
    }


// ScrollView {

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

       ScrollView {
           width: window.width > 1023 ? parent.width*1/3 : parent.width/2
           height: 500
           clip: true

     ColumnLayout {
       width: parent.width
       Equation {
         id: equation
         Component.onCompleted: {
//             console.log("Equation :")
             setVariables(root.sensorId, SensorsList.getEquationType(root.sensorId), SensorsList.getEquationA(root.sensorId),
                          SensorsList.getEquationB(root.sensorId),
                          SensorsList.getEquationC(root.sensorId), SensorsList.getEquationD(root.sensorId), SensorsList.getEquationE(root.sensorId))
             refresh();
         }
         onConfigSelected: {
             equationPopup.setVariables(root.sensorId, SensorsList.getEquationType(root.sensorId), SensorsList.getEquationA(root.sensorId), SensorsList.getEquationB(root.sensorId),
                          SensorsList.getEquationC(root.sensorId), SensorsList.getEquationD(root.sensorId), SensorsList.getEquationE(root.sensorId));
             equationPopup.open();
         }
       }

       Configs {
           id: configs
           Layout.topMargin: 5
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
           width: 400

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
                   Layout.alignment: Qt.AlignHCenter
                   text: qsTr(root.humidityOut)
               }
           }
       }
      }
      Pane {
           id: pane5
           Layout.fillWidth: true
           RowLayout {
//              width: parent.width
              width: 400
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

              ComboBox {
                  id: resTypeCombo
                  property var resTypes: [ "X=r/r0", "X=dr/r0" ]
                  function getIndex() {
                      var xType = SensorsList.getXType(root.sensorId)
                      for(var i=0; i< resTypes.length; i++) {
                          if(resTypes[i] === xType) {
                              return i;
                          }
                      }
                      return 0;
                  }

                  width: 200
                  model: resTypes
                  currentIndex: getIndex()
                  onActivated:SensorsList.setXType(root.sensorId, resTypes[currentIndex])
              }
           }
      }
      Pane {
           id: pane3
           Layout.fillWidth: true

           RowLayout {
              width: 300
              spacing: 5
              ColumnLayout {

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
                      id: pressureValue
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr("0")

                  }
              }


// Res
              ColumnLayout {

//                  Label {
//                      text: "RES"
//                      font.pixelSize: 22
//                  }
                  Text {
                      id: xValue
                      font.pixelSize: 20
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr("X : "+SensorsList.getX(sensorId))
                  }

                  Text {
                      id: res
                      font.pixelSize: 20
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr("R : "+SensorsList.getRes(sensorId))
                  }
              }
// Temperature
              ColumnLayout {

//                  Label {
//                      text: "TEMP"
//                      font.pixelSize: 22
//                  }

                  Text {
                      id: temp
                      font.pixelSize: 20
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr("T: "+SensorsList.getTemp(sensorId))
                  }
              }

          }
      }

      Pane {
           id: pane4
           Layout.fillWidth: true
           RowLayout {
               spacing: 5
               ColumnLayout {
                   Label {
                      Layout.alignment: Qt.AlignHCenter
                      text: "Flow Er"
                      font.pixelSize: 20
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
                      text: "Electrical Er"
                      font.pixelSize: 20
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
                      font.pixelSize: 20
                   }
                   StatusIndicator {
                       Layout.alignment: Qt.AlignHCenter
                       color: "green"
                       active: root.charging
                   }
               }
               ColumnLayout {
                   Label {
                      Layout.alignment: Qt.AlignHCenter
                      text: "Active"
                      font.pixelSize: 20
                   }
                   StatusIndicator {
                           color: "green"
                           active: root.sensorActive
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
                           pump.Material.background =  Material.red;
                       } else {
                           onOff = true;
                           pump.Material.background =  Material.Green;
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
                           rec.Material.background =  Material.red;
                           BackEnd.turnOffHeater(root.sensorId);
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
                           heaterStart.Material.background =  Material.red;
                           BackEnd.turnOffHeater(root.sensorId);
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



      Rectangle {
          width: parent.width
          height: 70
//          color: "red"
      }
     }
       }
   }

// }
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
//                   Layout.topMargin: 40
                   Layout.bottomMargin: 20
                   Layout.alignment: Qt.AlignHCenter
               }
               TextFieldWithBorder {
                   id: configTextEdit
                   text: qsTr(popup.configValue)
//                   onActiveFocusChanged: BackEnd.openKeyboard()
//                   Layout.fillWidth: true
                   implicitWidth: 100
                   height: 50
//                   width: 250
                   font.pixelSize: 22
                   Layout.alignment: Qt.AlignHCenter
                   horizontalAlignment: TextInput.AlignHCenter
               }
//               Rectangle {
//                   anchors.top: configTextEdit.bottom
//                   width: parent.width
//                   height: 60
//               }

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
//                             console.log("config submite");
//                             console.log(root.sensorId);
//                             console.log(configTextEdit.text);
                             if(popup.configId === 1) {
                               SensorsList.setFilterValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 2) {
                                 SensorsList.setR0Value(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 3) {
                                 SensorsList.setRtolValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 4) {
                                 BackEnd.setPumpValue(configTextEdit.text);
                             } else if(popup.configId === 5) {
                                 SensorsList.setOperationTempValue(root.sensorId, configTextEdit.text);
                             } else if(popup.configId === 6) {
                                 SensorsList.setTRtolValue(root.sensorId, configTextEdit.text);
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
               if(SensorsList.getRes(sensorId).toFixed(2) > 160000) {
                  res.text = "R: -" ;
               } else {
                  res.text =  "R: "+SensorsList.getRes(sensorId).toFixed(2);
               }

               temp.text = "T: "+SensorsList.getTemp(sensorId).toFixed(2);
               pressureValue.text = SensorsList.getPressure(sensorId);
               if(SensorsList.getX(sensorId).toFixed(2) > 160000) {
                   xValue.text = "X : -";
               } else {
                   xValue.text = "X : "+SensorsList.getX(sensorId).toFixed(2);
               }

               if(SensorsList.getSensorActiveValue(root.sensorId) === 1) {
                   root.sensorActive = true ;
               } else { root.sensorActive = false ; }
               root.flowError = BackEnd.getFlowErrorStatus();
               root.electricalError = BackEnd.getElectricalErrorStatus();
               root.charging = BackEnd.getChargingStatus();
               root.humidityIn = BackEnd.getHumidityIn();
               root.humidityOut = BackEnd.getHumidityOut();
               root.humidityArea = BackEnd.getHumidityArea();
               //               configs.updateConfig();
//               console.log("trigerred "+sensorId);
//               console.log(SensorsList.getTemp(sensorId) );
//               console.log(SensorsList.getRes(sensorId) );
           }
    }
}
