import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Pane {
    id: root
    implicitHeight: 80
    implicitWidth: parent.width*0.94
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
//        console.log("equation setVariables:"+sId+", "+eType+", "+a1+", "+b1+", "+c1+", "+d1+", "+e1);
        root.a=a1; root.b=b1; root.c=c1; root.d=d1; root.e=e1; root.equationType=eType; root.sensorId = sId;
    }
    function setCoefficients(temp) {coefficients = temp;}
    function setPowers(temp) {powers = temp;}
    signal configSelected()

    function refresh(){
//        console.log("Equation referesh");
        if(root.equationType == 0) {
//            console.log("equation 0");
//            console.log(root.a+","+root.b+","+root.c+","+root.d+","+root.e);
            equation0.visible = true;
            equation1.visible = false;
            c0a.setCoefficient(root.a); c0b.setCoefficient("+ "+root.b);
            c0c.setCoefficient("+ "+root.c); c0d.setCoefficient("+ "+root.d);
            c0e.setCoefficient("+ "+root.e);
        } else if(root.equationType == 1) {
//            console.log("equation 1");
//            console.log(root.a+","+root.b+","+root.c+","+root.d+","+root.e);
            equation1.visible = true;
            equation0.visible = false;
            c1ab.setCoefficient(root.a); c1ab.setPower(root.b);
            c1cd.setCoefficient(root.c); c1cd.setPower(root.d);
        }

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
        spacing: 0
        EquationCoefficient {
            id: c0a
            Component.onCompleted: {
                setCoefficient(root.a);
                setPower("4");
                setVariable("X");
            }
            implicitWidth: 60
        }
        EquationCoefficient {
            id: c0b
            Component.onCompleted: {
                setCoefficient("+ "+root.b);
                setPower("3");
                setVariable("X");
            }
        }
        EquationCoefficient {
            id: c0c
            Component.onCompleted: {
                setCoefficient("+ "+root.c);
                setPower("2");
                setVariable("X");
            }
        }
        EquationCoefficient {
            id: c0d
            Component.onCompleted: {
                setCoefficient("+ "+root.d);
                setPower("1");
                setVariable("X");
            }
        }
        EquationCoefficient {
            id: c0e
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
            id: c1ab
            Component.onCompleted: {
                setCoefficient(root.a);
                setPower(root.b);
                setVariable("e");
            }
        }
        EquationCoefficient {
            id: c1cd
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
