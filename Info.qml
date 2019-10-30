import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import SensorModel 1.0

Page {
    id: root


    ColumnLayout {
        anchors.fill: parent

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            id: listView
            spacing: 10
            model: SensorModel {
                list: SensorsList
            }

            delegate: SensorInfo {
                Component.onCompleted: {
                    setTemp(model.tempActive);
                    setHeater(model.heaterActive);
                    setSensorActive(model.sensorActive);
                    setSensorName(model.gasType);
                    setProgressValue(0);
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true

          RowLayout {
              width: parent.width

            Image {
                sourceSize.width: 100
                sourceSize.height: 100
                source: "images/pumpBlack.png"
            }

            ColumnLayout {

                Label {
                    text: "Area"
                    font.pixelSize: 22
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("DC")
                }
            }

            ColumnLayout {

                Label {
                    text: "In"
                    font.pixelSize: 22
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("DC")
                }
            }
            ColumnLayout {

                Label {
                    text: "Out"
                    font.pixelSize: 22
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("DC")
                }
            }

            Button {
                text: qsTr("Start")
                highlighted: true
                Material.background: Material.Teal
            }

            Button {
                text: qsTr("Login")
                highlighted: true
                Material.background: Material.Green
                onClicked: root.StackView.view.push("qrc:/Login.qml")
            }

          }

        }

    }
}
