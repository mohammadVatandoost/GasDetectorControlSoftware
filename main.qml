import QtQuick 2.9
import QtQuick.Window 2.2
//import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.FreeVirtualKeyboard 1.0
import QtQuick.Extras 1.4

Window {
    id: window
    visible: true
    width: 768
    height: 640
//    title: qsTr("Hello World")
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: SplashScreen {}
//        transitions: []
         popExit: Transition {}
         pushEnter: Transition {}
         popEnter: Transition {}
         pushExit: Transition {}
    }

    InputPanel {
        id: inputPanel
        z: 1000
        y: stackView.height
        anchors.left: parent.left
        anchors.right: parent.right
        states: State {
            name: "visible"
            when: Qt.inputMethod.visible
            PropertyChanges {
                target: inputPanel
                y: stackView.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 150
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

//    TabView {
//        anchors.fill: parent
//        Tab {
//             title: "Channels Configuration/Monitoring"
//             Info {
//                 anchors.centerIn: parent
//             }
//        }
//        Tab {
//            title: "EEW Configuration"
//        }
//        Tab {
//            title: "SHM Configuration"
//        }
//        Tab {
//            title: "Charts"
//        }
//    }

}
