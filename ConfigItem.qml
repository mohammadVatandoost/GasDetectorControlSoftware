import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

//Rectangle {
Pane {
    id: root
    width: 95
    height: 80
    Material.elevation: 6
//    scale:  mouseArea.containsMouse ? 0.8 : 1.0
//    smooth: mouseArea.containsMouse


    property int configId
    property string configName: ""
    property string configValue: ""
    function setConfigId(temp) {configId = temp;}
    function setConfigName(temp) {configName = temp;}
    function setConfigValue(temp) {configValue = temp;}
    signal configSelected(int configId, string configName, string configValue)

//    Rectangle {
//        id: paddingRectangle
//        anchors.top: root.top
//        width: parent.width
//        height: 12
////        color: "red"
//    }
    Rectangle {
        id: paddingRectangle
//        anchors.top: root.top
        y: 1
        width: parent.width*0.9
        anchors.horizontalCenter: parent.horizontalCenter
        height: 4
//        color: "red"
    }

    Text {
        id: valueText
        anchors.top: paddingRectangle.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr(configValue)
        font.pointSize: 20
        font.bold: true
    }

    Rectangle {
        id: paddingRectangle2
        anchors.top: valueText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*0.9
        height: 4
//        color: "blue"
    }

    Text {
        anchors.top: paddingRectangle2.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr(configName)
        font.pointSize: 15
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        anchors.margins: -10
        onClicked: { root.configSelected(configId, configName, configValue) }
        hoverEnabled: true
    }


}
