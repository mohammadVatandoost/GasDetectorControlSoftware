import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.VirtualKeyboard 2.1

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
        width: root.width
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
        InputPanel {
            Layout.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
//            active: true
            width: 80
//            inputMethodHints: Qt.ImhDigitsOnly
        }

        InputMethod {
            function inputModes(locale) {
                return [InputEngine.Latin];
            }

            function setInputMode(locale, inputMode) {
                return true
            }

            function setTextCase(textCase) {
                return true
            }

            function reset() {
                // TODO: reset the input method without modifying input context
            }

            function update() {
                // TODO: commit current state and update the input method
            }

            function keyEvent(key, text, modifiers) {
                var accept = false
                // TODO: Handle key and set accept or fallback to default processing
                return accept;
            }
        }
//        TextEdit {
//            id: textEdit
//            Layout.topMargin: 40
//            Layout.bottomMargin: 20
//            width: 200
//            height: 50
//            font.pointSize: 25
//            inputMethodHints: Qt.ImhDigitsOnly
//            property string placeholderText: "Enter Password"

//            Text {
//                text: textEdit.placeholderText
//                color: "#aaa"
//                font.pointSize: 25
//                visible: !textEdit.text && !textEdit.activeFocus // <----------- ;-)
//            }
//        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Login")
            highlighted: true
            Material.background: Material.Green
            onClicked: root.StackView.view.push("qrc:/Setting.qml")
        }
    }


}
