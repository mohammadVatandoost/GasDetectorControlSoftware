import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

//Rectangle {
Pane {
    id: root
    implicitHeight: 100
    implicitWidth: parent.width
    Material.elevation: 6
//    Layout.bottomMargin: 50
//    scale:  mouseArea.containsMouse ? 0.8 : 1.0
//    smooth: mouseArea.containsMouse

    property int configId
    property string configName: ""
    property string configValue: ""
    function setConfigId(temp) {configId = temp;}
    function setConfigName(temp) {configName = temp;}
    function setConfigValue(temp) {configValue = temp;}
    signal configSelected(int configId, string configName, string configValue)

    RowLayout {
        EquationCoefficient {
        }
        EquationCoefficient {
        }
        EquationCoefficient {
        }

    }




    MouseArea {
        id: mouseArea
        anchors.fill: parent
        anchors.margins: -10
        onClicked: { root.configSelected(configId, configName, configValue) }
        hoverEnabled: true
    }


}
