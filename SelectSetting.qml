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
            text: "Setting"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    Grid {
      columns: 2
      width: 860
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      spacing: 60

      Pane {
          width: 400
          height: 200
          Material.elevation: 6

          Text {
//              anchors.top: paddingRectangle.bottom
              anchors.horizontalCenter: parent.horizontalCenter
              anchors.verticalCenter: parent.verticalCenter
              text: qsTr("Gas Sensors Setting")
              font.pointSize: 20
              font.bold: true
          }


          MouseArea {
              id: mouseArea
              anchors.fill: parent
              anchors.margins: -10
              onClicked: { root.StackView.view.push("qrc:/Setting.qml"); }
              hoverEnabled: true
          }

      }

      Pane {
          width: 400
          height: 200
          Material.elevation: 6

          Text {
              anchors.verticalCenter: parent.verticalCenter
              anchors.horizontalCenter: parent.horizontalCenter
              text: qsTr("Brooks Setting")
              font.pointSize: 20
              font.bold: true
          }


          MouseArea {
              anchors.fill: parent
              anchors.margins: -10
              onClicked: { root.StackView.view.push("qrc:/Brooks.qml"); }
              hoverEnabled: true
          }

      }

    }

}

