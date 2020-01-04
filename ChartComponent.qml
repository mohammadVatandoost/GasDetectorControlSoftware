import QtQuick 2.0
import QtCharts 2.0


ChartView {
//    title: "Y"
//    width: 400
    height: window.height*0.9
    antialiasing: true
    id: root
    property int sensorId: 0
    function setSensorId(temp) {sensorId = temp;}

    DateTimeAxis {
        id: axisXTime
        format: "mm:ss"
        tickCount: 10
        Component.onCompleted: {
           BackEnd.setAxisXTime(axisXTime);
        }
    }

    ValueAxis {
        id: tempYData
        min: 0
        max: 500
    }

    ValueAxis {
        id: resYData
        min: 0
        max: 1000
    }

    LineSeries {
        id: lineSeriesRes
        axisX: axisXTime
        axisYRight: resYData
        name: "Res"
    }
    LineSeries {
        id: lineSeriesTemp
        axisX: axisXTime
        axisY: tempYData
        name: "Temp"
    }


    Timer {
        id: refreshTimer
        interval: 1000//30 // 60 Hz
        running: true
        repeat: true
        onTriggered: {

            BackEnd.updateChart(lineSeriesTemp, root.sensorId);
            BackEnd.updateChart(lineSeriesRes, root.sensorId);
//            tempYData.min = BackEnd.getSensorTempMin();
//            tempYData.max = BackEnd.getSensorTempMax();

//            resYData.min = BackEnd.getSensorResMin();
//            resYData.max = BackEnd.getSensorResMax();
        }
    }

}
