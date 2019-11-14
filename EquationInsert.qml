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
        property int sensorId: 0
        property int configId
        property int equationType: 0
        property string configName: "test"
        property string configValue: "test"
        property var coefficients: []
        property var powers: []
        property string a: ""
        property string b: ""
        property string c: ""
        property string d: ""
        property string e: ""
        function setCoefficients(temp) {coefficients = temp;}
        function setPowers(temp) {powers = temp;}
        function setConfigId(temp) {configId = temp;}
        function setConfigName(temp) {configName = temp;}
        function setConfigValue(temp) {configValue = temp;}
        function setVariables(sId, eType, a1, b1, c1, d1, e1) {
            a=a1; b=b1; c=c1; d=d1; e=e1; equationType=eType; sensorId = sId;
        }
        signal configSet(int configId, string configName, string configValue)

        function refresh(){
            atextinput.text = a;
            btextinput.text = b;
            ctextinput.text = c;
            dtextinput.text = d;
            etextinput.text = e;
            if(equationType == 0) {
                equation0RadioBtn.checked = true;
            } else if(equationType == 1) {
                equation1RadioBtn.checked = true;
            }

//              for(var i=0; i<coefficients.length; i++) {
//                   console.log("equetion for");console.log(coefficients[i]);console.log(powers[i])
//                   var component = Qt.createComponent("EquationCoefficient.qml");
//                   var object = component.createObject(equation)
//                   if(coefficients[i] < 0) {
//                       object.setCoefficient("-"+ coefficients[i])
//                       object.setPower( powers[i])
//                   } else {
//                       if(i==0) {
//                           object.setCoefficient(coefficients[i])
//                           object.setPower( powers[i])
//                       } else {
//                           object.setCoefficient("+"+ coefficients[i])
//                           object.setPower( powers[i])
//                       }
//                   }
//              }
         }

        Component.onCompleted: {
            refresh();
        }

        ColumnLayout {
            anchors.fill: parent

//            Pane {
//                implicitHeight: 100
//                implicitWidth: parent.width*0.8
//                anchors.horizontalCenter: parent.horizontalCenter
//                Material.elevation: 6

//                RowLayout {
//                  id: equation
//                }
//            }
            ButtonGroup { id: radioGroup }
            Pane {
                 implicitHeight: 100
                 implicitWidth: parent.width*0.8
                 anchors.horizontalCenter: parent.horizontalCenter
                 Material.elevation: 6

                 RowLayout {
                     RadioButton {
                         id: equation0RadioBtn
                         text: qsTr("");
                         checked: true
                         ButtonGroup.group: radioGroup
                         onClicked: {
                             console.log("equation 1")
                             econtainer.visible = true;
                             popup.equationType = 0;
                         }
                     }
                     EquationCoefficient {
                         Component.onCompleted: {
                             setCoefficient("A");
                             setPower("4");
                             setVariable("X");
                         }
                     }
                     EquationCoefficient {
                         Component.onCompleted: {
                             setCoefficient("+ B");
                             setPower("3");
                             setVariable("X");
                         }
                     }
                     EquationCoefficient {
                         Component.onCompleted: {
                             setCoefficient("+ C");
                             setPower("2");
                             setVariable("X");
                         }
                     }
                     EquationCoefficient {
                         Component.onCompleted: {
                             setCoefficient("+ D");
                             setPower("1");
                             setVariable("X");
                         }
                     }
                     EquationCoefficient {
                         Component.onCompleted: {
                             setCoefficient("+ E");
                             setPower("");
                             setVariable("");
                         }
                     }
                 }
             }

            Pane {
                 implicitHeight: 100
                 implicitWidth: parent.width*0.8
                 anchors.horizontalCenter: parent.horizontalCenter
                 Material.elevation: 6

                 RowLayout {
                     RadioButton {
                         id: equation1RadioBtn
                         text: qsTr("");
                         checked: false
                         ButtonGroup.group: radioGroup
                         onClicked: {
                             console.log("equation 2")
                             econtainer.visible = false;
                             popup.equationType = 1;
                         }
                     }
                     EquationCoefficient {
                         Component.onCompleted: {
                             setCoefficient("A");
                             setPower("B");
                             setVariable("e");
                         }
                     }
                     EquationCoefficient {
                         Component.onCompleted: {
                             setCoefficient("+ C");
                             setPower("D");
                             setVariable("e");
                         }
                     }
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
                    ColumnLayout {
                        Label {
                            text: "A"
                            font.pixelSize: 22
                            Layout.alignment: Qt.AlignHCenter
                        }
                       TextInputBorder {id: atextinput}
                    }
                    ColumnLayout {
                        Label {
                            text: "B"
                            font.pixelSize: 22
                            Layout.alignment: Qt.AlignHCenter
                        }
                       TextInputBorder {id: btextinput}
                    }
                    ColumnLayout {
                        Label {
                            text: "C"
                            font.pixelSize: 22
                            Layout.alignment: Qt.AlignHCenter
                        }
                       TextInputBorder {id: ctextinput}
                    }
                    ColumnLayout {
                        Label {
                            text: "D"
                            font.pixelSize: 22
                            Layout.alignment: Qt.AlignHCenter
                        }
                       TextInputBorder {id: dtextinput}
                    }
                    ColumnLayout {
                        id: econtainer
                        Label {
                            text: "E"
                            font.pixelSize: 22
                            Layout.alignment: Qt.AlignHCenter
                        }
                       TextInputBorder {id: etextinput}
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
                          SensorsList.setEquationType(sensorId, equationType);
                          SensorsList.setEquationA(sensorId, a);
                          SensorsList.setEquationB(sensorId, b);
                          SensorsList.setEquationC(sensorId, c);
                          SensorsList.setEquationD(sensorId, d);
                          SensorsList.setEquationE(sensorId, e);
                          popup.close();
                      }
                      Layout.alignment: Qt.AlignHCenter
                  }

              }

            }

        }
 }
