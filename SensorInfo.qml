import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
    property bool tempActive: false
    property bool heaterActive: false
    Image {
        sourceSize.width: 60
        sourceSize.height: 60
        source: tempActive ?  "images/greenTemp.png" : "images/blackTemp.jpeg"
    }
    Text {
        id: temp1
        text: qsTr("temp1")
    }
    Image {
        sourceSize.width: 60
        sourceSize.height: 60
        source: heaterActive ?  "images/heaterRed.png" : "images/heaterBlack.png"
    }
    Text {
        id: h1
        text: qsTr("H1")
    }
    Text {
        text: qsTr("NO")
    }
    ProgressBar {
        value: 0.5
    }
    Text {
        text: qsTr("DC")
    }
    StatusIndicator {
            color: "green"
            active: true
    }
}
