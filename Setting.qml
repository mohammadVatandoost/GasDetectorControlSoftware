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

    Drawer {
            id: drawer
            width: 0.66 * window.width
            height: window.height
       ColumnLayout {
            anchors.fill: parent
            spacing: 2

            Rectangle {
                width: parent.width
                height: 70

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Sensor 1")
                    font.pointSize: 20
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: { parent.color = 'red' }
                }

                Rectangle {
                        id: borderBottom
                        width: parent.width
                        height: 1
                        anchors.bottom: parent.bottom
                        color: "black"
               }
            }
       }
     }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        //        TextField {
        //           id: textEdit
        //           width: 400
        //           leftPadding: 10
        //           anchors.horizontalCenter: parent.horizontalCenter
        //           property string placeholderText: "Enter Password"

        //           Text {
        //               text: textEdit.placeholderText
        //                color: "#aaa"
        //                visible: !textEdit.text
        //           }
        //        }

        TextEdit {
            id: textEdit
            Layout.topMargin: 40
            Layout.bottomMargin: 20
            width: 200
            height: 50
            font.pointSize: 25
            inputMethodHints: Qt.ImhDigitsOnly
//            anchors.horizontalCenter: parent.horizontalCenter
            property string placeholderText: "Enter Password"

            Text {
                text: textEdit.placeholderText
                color: "#aaa"
                font.pointSize: 25
                visible: !textEdit.text && !textEdit.activeFocus // <----------- ;-)
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Login")
            highlighted: true
            Material.background: Material.Green
            onClicked: root.StackView.view.push("qrc:/ControlPanel.qml")
        }
    }


}
