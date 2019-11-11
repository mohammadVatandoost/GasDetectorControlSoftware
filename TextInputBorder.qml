import QtQuick 2.4

Item {
    id: root
    property int fontSize: 18
    property string text: "Type here..."
    implicitHeight: input.font.pixelSize*1.5
    implicitWidth: 60
    Rectangle{
        id: body
        color: "transparent"
        anchors.fill: parent
        border {
            width: 1
        }
        TextInput{
            id: input
            anchors {
                fill: parent
            }
            font.pointSize: fontSize
            selectByMouse: true
            layer.enabled: true
        }
    }
}
