import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Pane {
    id: root
    implicitHeight: 100
    implicitWidth: parent.width
    Material.elevation: 6

    property int configId
    property var coefficients: []
    property var powers: []
    function setCoefficients(temp) {coefficients = temp;}
    function setPowers(temp) {powers = temp;}
    signal configSelected()

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

    RowLayout {
        id: equation
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        anchors.margins: -10
        onClicked: { root.configSelected() }
        hoverEnabled: true
    }
}
