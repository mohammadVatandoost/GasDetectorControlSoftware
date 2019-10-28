import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Drawer {
        id: root
        width: 0.66 * window.width
        height: window.height
        signal sensorSelect(int sensorId)
// Pane {
//    id: pane
//    Layout.fillWidth: true
//    Layout.fillHeight: true

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        NavigationItem {
          Component.onCompleted: setSensorId(1)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(2)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(3)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(4)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(4)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(4)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(4)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(4)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
        NavigationItem {
          Component.onCompleted: setSensorId(4)
          onSensorSelected : {root.sensorSelect(sensorId);}
        }
    }
//  }
}
