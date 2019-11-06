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
    function setCoefficient(temp) {coefficient = temp;}
    function setPower(temp) {power = temp;}
    ColumnLayout {
        Text {
            text: qsTr(root.power)
            font.pixelSize: 18
            Layout.leftMargin: 30
            Layout.topMargin: 0
            Layout.bottomMargin: 0

        }
        Text {
            text: qsTr(coefficient + " X")
            font.pixelSize: 22
            Layout.topMargin: -10
            Layout.bottomMargin: 0
        }
    }

}
