import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Pane {
    id: root
    implicitHeight: 100
    implicitWidth: parent.width*0.8
    Material.elevation: 6

    property int configId
    property var coefficients: []
    property var powers: []
    property int sensorId: 0
    property int equationType: 0
    property string a: ""
    property string b: ""
    property string c: ""
    property string d: ""
    property string e: ""
    function setVariables(sId, eType, a1, b1, c1, d1, e1) {
        a=a1; b=b1; c=c1; d=d1; e=e1; equationType=eType; sensorId = sId;
    }
    function setCoefficients(temp) {coefficients = temp;}
    function setPowers(temp) {powers = temp;}
    signal configSelected()

    function refresh(){
//          for(var i=0; i<coefficients.length; i++) {
//               console.log("equetion for");console.log(coefficients[i]);console.log(powers[i])
//               var component = Qt.createComponent("EquationCoefficient.qml");
//               var object = component.createObject(equation)
//               if(coefficients[i] < 0) {
//                   object.setCoefficient("-"+ coefficients[i])
//                   object.setPower( powers[i])
//               } else {
//                   if(i==0) {
//                       object.setCoefficient(coefficients[i])
//                       object.setPower( powers[i])
//                   } else {
//                       object.setCoefficient("+"+ coefficients[i])
//                       object.setPower( powers[i])
//                   }
//               }
//          }
     }

    Component.onCompleted: {
        refresh();
    }

    RowLayout {
        id: equation0
        EquationCoefficient {
            Component.onCompleted: {
                setCoefficient(root.a);
                setPower("4");
                setVariable("X");
            }
        }
        EquationCoefficient {
            Component.onCompleted: {
                setCoefficient("+ "+root.b);
                setPower("3");
                setVariable("X");
            }
        }
        EquationCoefficient {
            Component.onCompleted: {
                setCoefficient("+ "+root.c);
                setPower("2");
                setVariable("X");
            }
        }
        EquationCoefficient {
            Component.onCompleted: {
                setCoefficient("+ "+root.d);
                setPower("1");
                setVariable("X");
            }
        }
        EquationCoefficient {
            Component.onCompleted: {
                setCoefficient("+ "+root.e);
                setPower("");
                setVariable("");
            }
        }
    }

    RowLayout {
        id: equation1
        EquationCoefficient {
            Component.onCompleted: {
                setCoefficient(root.a);
                setPower(root.b);
                setVariable("e");
            }
        }
        EquationCoefficient {
            Component.onCompleted: {
                setCoefficient("+ "+root.c);
                setPower(root.d);
                setVariable("e");
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        anchors.margins: -10
        onClicked: { root.configSelected() }
        hoverEnabled: true
    }
}
