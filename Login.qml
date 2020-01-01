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
            text: "Login"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        width: 1000

        Label {
            id: errorMessage

            text: ""
            font.pixelSize: 22
            anchors.centerIn: parent
            color: "red"
        }


        TextFieldWithBorder {
            id: textEdit
            width: 1000
            Layout.topMargin: 150
            Layout.alignment: Qt.AlignHCenter
            echoMode: TextInput.Password
            placeholderText: "Password field"
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
            enterKeyAction: EnterKeyAction.Next
            onAccepted: upperCaseField.focus = true
        }


        Button {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Login")
            highlighted: true
            Material.background: Material.Green
            Layout.topMargin: 40
            onClicked: {
                console.log(textEdit.text);
                root.StackView.view.push("qrc:/Setting.qml");
                if(textEdit.text == "1234") {
                   root.StackView.view.push("qrc:/Setting.qml");
                } else {
                  errorMessage.text = "Your password is wrong";
                }
            }
        }
    }

}

//        TextField {
//            id: textEdit
//            anchors.top: errorMessage.bottom
//            Layout.topMargin: 30
//            Layout.bottomMargin: 20
//            Layout.leftMargin: 20
//            width: 200
//            height: 50
//            font.pointSize: 25
//            inputMethodHints: Qt.ImhHiddenText
//            echoMode: TextInput.Password
////            property string placeholderText: "Enter Password"
////            onActiveFocusChanged: BackEnd.openKeyboard()
//            Text {
//                width: parent.width
//                text: "Enter Password"
//                color: "#aaa"
//                font.pointSize: 25
//                visible: !textEdit.text && !textEdit.activeFocus
//            }
//        }
