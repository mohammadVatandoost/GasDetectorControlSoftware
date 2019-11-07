import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Popup {
        id: popup
        padding: 10
        width: parent.width
        height: parent.height
//            x: Math.round((parent.width - width) / 2)
//            y: Math.round((parent.height - height) / 2)
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        property int configId
        property string configName: "test"
        property string configValue: "test"
        property var coefficients: []
        property var powers: []

        function setCoefficients(temp) {coefficients = temp;}
        function setPowers(temp) {powers = temp;}
        function setConfigId(temp) {configId = temp;}
        function setConfigName(temp) {configName = temp;}
        function setConfigValue(temp) {configValue = temp;}
        signal configSet(int configId, string configName, string configValue)

        function refresh(){
              for(var i=0; i<coefficients.length; i++) {
                   console.log("equetion for");console.log(coefficients[i]);console.log(powers[i])
                   var component = Qt.createComponent("EquationCoefficient.qml");
                   var object = component.createObject(equation)
                   if(coefficients[i] < 0) {
                       object.setCoefficient("-"+ coefficients[i])
                       object.setPower( powers[i])
                   } else {
                       if(i==0) {
                           object.setCoefficient(coefficients[i])
                           object.setPower( powers[i])
                       } else {
                           object.setCoefficient("+"+ coefficients[i])
                           object.setPower( powers[i])
                       }
                   }
              }
         }

        Component.onCompleted: {
            refresh();
        }

        ColumnLayout {
            anchors.fill: parent

            Pane {
                implicitHeight: 100
                implicitWidth: parent.width*0.8
                anchors.horizontalCenter: parent.horizontalCenter
                Material.elevation: 6

                RowLayout {
                  id: equation
                }
            }

            Pane {
                implicitHeight: 100
                implicitWidth: parent.width*0.8
                anchors.horizontalCenter: parent.horizontalCenter
                Material.elevation: 6

                RowLayout {
                    width: parent.width
                    height: 100
                    TextEdit {
                        width: 110
                        height: 20
                        font.pixelSize: 12
                        focus: true
                    }
                    TextEdit {
                        width: 110
                        height: 20
                        font.pixelSize: 12
                        focus: true
                    }
                    Button {
                        text: qsTr("Add")
                        highlighted: true
                        Material.background: Material.Green
                        onClicked: {
                            popup.close();
                        }
                    }
                }
                RowLayout {
                    width: parent.width
                    height: 100
                    Button {
                        text: qsTr("Remove")
                        highlighted: true
                        Material.background: Material.Red
                        onClicked: {
                            popup.close();
                        }
//                        Layout.alignment: Qt.AlignHCenter
                    }
                }
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
                          popup.close();
                      }
                      Layout.alignment: Qt.AlignHCenter
                  }

              }

            }

        }
 }
