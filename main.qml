import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    TabView {
        anchors.fill: parent
        Tab {
             title: "Channels Configuration/Monitoring"
             Info {
                 anchors.centerIn: parent
             }
        }
        Tab {
            title: "EEW Configuration"
        }
        Tab {
            title: "SHM Configuration"
        }
        Tab {
            title: "Charts"
        }
    }

}
