import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Window {
    id: window
    visible: true
    width: 768
    height: 640
//    title: qsTr("Hello World")
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Info {}
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
