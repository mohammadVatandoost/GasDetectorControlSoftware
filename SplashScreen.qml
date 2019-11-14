import QtQuick 2.0
import QtQuick.Controls 2.4

Page {
    id: root

    Image {
      sourceSize.width: 400
      sourceSize.height: 400
      source: "images/oilCompany.png"
      anchors.centerIn: parent
      anchors.verticalCenter: parent.verticalCenter
    }

    Timer {
            interval: 1000; running: true; repeat: false
            onTriggered: root.StackView.view.push("qrc:/Info.qml")
        }

}
