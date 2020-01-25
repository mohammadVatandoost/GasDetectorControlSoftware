import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
    id: root
    width: parent.width*0.8
    spacing: 10
    anchors.horizontalCenter: parent.horizontalCenter

    property string gasType: "NO"
    property double spRateReaded: 21.02
    property double spRate: 20.02
    property int channelId: 1
    property int vor: 2

    function setSpRate(temp) { spRate = temp;}
    function setChannelId(temp) {channelId = temp;}
    function setGasType(temp) {gasType = temp;}
    function setSpRateReaded(temp) { spRateReaded = temp;}

    signal channelSelected(int channelId, double spRate);

    ComboBox {
        id: comboBoxGas
        property var gasTypes: [ "NO", "CO", "SO2", "O2", "BTEX", "VOC" ]
        function getIndex() {
//            var gasType = 0; //SensorsList.getGasTypeValue(root.sensorId)
            for(var i=0; i< gasTypes.length; i++) {
                if(gasTypes[i] === root.gasType) {
                    return i;
                }
            }
            return 0;
        }

        width: 200
        model: gasTypes
        currentIndex: getIndex()
        onActivated: BackEnd.setChannelName(root.channelId, gasTypes[currentIndex])
    }
    Text {
        id: temp1
        text: qsTr("SP Rate :")
        font.pixelSize: 22
    }
    Text {
        id: spRateText
        text: qsTr(root.spRateReaded.toFixed(2)+" mA")
        font.pixelSize: 22
    }

    Button {
        id: openBtn
        text: qsTr("Open")
        highlighted: true
        Material.background: (root.vor === 1) ? Material.Green : Material.red
        onClicked: {
            root.vor = 1;
            BackEnd.setChannelVOR(root.channelId, root.vor);
        }
    }

    Button {
        id: normalBtn
        text: qsTr("Normal")
        highlighted: true
        Material.background: (root.vor === 0) ? Material.Green : Material.red
        onClicked: {
            root.vor = 0;
            BackEnd.setChannelVOR(root.channelId, root.vor);
        }
    }

    Button {
        id: closeBtn
        text: qsTr("Close")
        highlighted: true
        Material.background: (root.vor === 2) ? Material.Green : Material.red
        onClicked: {
            root.vor = 2;
            BackEnd.setChannelVOR(root.channelId, root.vor);
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
