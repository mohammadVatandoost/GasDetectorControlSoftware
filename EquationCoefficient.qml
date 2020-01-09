import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Pane {
    id: root
    property string coefficient: "+5"
    property string power: "5"
    property string variable: "X"
    function setCoefficient(temp) {
        coefficient = temp;
    }
    function setPower(temp) {power = temp;}
    function setVariable(temp) {variable = temp;}
    implicitWidth: 80
    Layout.alignment: Qt.AlignLeft
    visible: (coefficient === "+ 0" || coefficient === "0") ? false : true
    ColumnLayout {
        Layout.alignment: Qt.AlignLeft

        Text {
            text: qsTr(root.power)
            font.pixelSize: 14
            Layout.leftMargin: coefficientText.width
            Layout.topMargin: 0
            Layout.bottomMargin: 0

        }
        Text {
            id: coefficientText
            text: qsTr(coefficient + " "+ variable)
            font.pixelSize: 18
            Layout.topMargin: -10
            Layout.bottomMargin: 0
        }
    }

}
