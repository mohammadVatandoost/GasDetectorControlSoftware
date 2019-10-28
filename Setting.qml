import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

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
            text: "Sensor 1"
            font.pixelSize: 20
            anchors.centerIn: parent
        }

        ToolButton {
            text: qsTr("Menu")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: drawer.open()
        }
    }

    NavigationDrawer {
        id: drawer
        onSensorSelect : {console.log("sensor id :" + sensorId);drawer.close();}
    }

   Grid {
       columns: window.width > 767 ? 2 : 1
       spacing: 2


   }

}
