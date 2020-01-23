import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
    id: root
    width: parent.width*0.45
    spacing: 10
    property string vor: "Closed"
    property double spRateReaded: 25.02
    property double spRate: 25.02
    property int channelId: 1

    function setSpRate(temp) { spRate = temp;}
    function setChannelId(temp) {channelId = temp;}
    signal channelSelected(int channelId, double spRate);

    Text {
        id: temp1
        text: qsTr("SP Rate :")
    }
    Text {
        id: spRateText
        text: qsTr(root.spRateReaded+" mA")
    }

    Button {
        id: openBtn
        text: qsTr("Open")
        highlighted: true
        Material.background: Material.red
        onClicked: {
            openBtn.Material.background =  Material.Green;
            closeBtn.Material.background =  Material.red;
            normalBtn.Material.background =  Material.red;
        }
    }

    Button {
        id: normalBtn
        text: qsTr("Normal")
        highlighted: true
        Material.background: Material.red
        onClicked: {
            normalBtn.Material.background =  Material.Green;
            openBtn.Material.background =  Material.red;
            closeBtn.Material.background =  Material.red;
        }
    }

    Button {
        id: closeBtn
        text: qsTr("Close")
        highlighted: true
        Material.background: Material.Green
        onClicked: {
            closeBtn.Material.background =  Material.Green;
            normalBtn.Material.background =  Material.red;
            openBtn.Material.background =  Material.red;
        }
    }

    Button {
        id: setRateBtn
        text: qsTr("set Sp Rate")
        highlighted: true
        Material.background: Material.Blue
        onClicked: {
           channelSelected(root.channelId, root.spRate)
        }
    }



}
