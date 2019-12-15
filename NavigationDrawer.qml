import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import SensorModel 1.0

Drawer {
        id: root
        width: 0.66 * window.width
        height: window.height
        signal sensorSelect(int sensorId)

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            id: listView
            spacing: 0
            model: SensorModel {
                list: SensorsList
            }

            delegate: NavigationItem {
                Component.onCompleted: {setSensorId(index);}
                onSensorSelected : {root.sensorSelect(sensorId);}
             }
        }

    }
}
