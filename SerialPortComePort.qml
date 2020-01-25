import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.FreeVirtualKeyboard 1.0
//import QtQuick.VirtualKeyboard 2.1

Page {
    id: root
    header: ToolBar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: "Choose come port"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    property var comePorts: BackEnd.getComePorts();
    Component.onCompleted: {
//      console.log("combox:");
//      console.log(BackEnd.getComePorts());
//        var temp = BackEnd.getComePorts();
//        for(var i=0; i<temp.length; i++) {
//            root.comePorts.push(temp[i]);
//            console.log(i+":"+temp[i]);
//            comboBoxGasSensors.model.append(temp[i]);
//        }
//        console.log("root.comports");
//        console.log(root.comePorts);
    }
    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        width: 1000
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            Text {
                text: qsTr("Gas Sensors: ")
            }
            ComboBox {
                id: comboBoxGasSensors
                width: 200
                model: BackEnd.getComePorts()
                currentIndex: 0
            }
        }
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            Text {
                text: qsTr("Brooks1: ")
            }
            ComboBox {
                id: comboBoxBrooks1
                width: 200
                model: BackEnd.getComePorts()
                currentIndex: 1
            }
        }
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            Text {
                text: qsTr("Brooks2: ")
            }
            ComboBox {
                id: comboBoxBrooks2
                width: 200
                model: BackEnd.getComePorts()
                currentIndex: 2
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Connect")
            highlighted: true
            Material.background: Material.Green
            Layout.topMargin: 20
            onClicked: {
                 console.log()
                 BackEnd.setComePorts( root.comePorts[comboBoxGasSensors.currentIndex], root.comePorts[comboBoxBrooks1.currentIndex], root.comePorts[comboBoxBrooks2.currentIndex]);
            }
        }


    }

}

