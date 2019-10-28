import QtQuick 2.0

Rectangle {
    id: root
    width: parent.width
    height: 60
    color: "red"
    property int sensorId
    function setSensorId(temp) {sensorId = temp;}
    signal sensorSelected(int sensorId)

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Sensor "+sensorId)
        font.pointSize: 20
    }

    MouseArea {
        anchors.fill: parent
        onClicked: { root.sensorSelected(sensorId) }
    }

    Rectangle {
            id: borderBottom
            width: parent.width
            height: 1
            anchors.bottom: parent.bottom
            color: "black"
   }
}
