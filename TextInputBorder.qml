import QtQuick 2.4
//import QtQuick.VirtualKeyboard 2.2

Item {
    id: root
    property int fontSize: 18
    property string text: "Type here..."
    signal textChangedS(string text )
    function getText() {
        return input.text
    }
    function setText(temp) {
        input.text = temp;
    }

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
//            leftPadding: 10
            anchors {
                fill: parent
            }
            font.pointSize: fontSize
            selectByMouse: true
            layer.enabled: true
            onTextChanged: {textChangedS(text)}
            onActiveFocusChanged: BackEnd.openKeyboard()
        }
    }
}
