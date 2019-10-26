import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
//import QtQuick.Controls.Styles 1.4

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
            text: Login
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

//    ColumnLayout {
//        width: 400
//        TextField {
//            style: TextFieldStyle {
//                textColor: "black"
//                background: Rectangle {
//                    radius: 2
//                    implicitWidth: 100
//                    implicitHeight: 24
//                    border.color: "#333"
//                    border.width: 1
//                }
//            }
//        }
//    }


}
