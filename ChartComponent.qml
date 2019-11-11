import QtQuick 2.0
import QtCharts 2.0


ChartView {
//    title: "Y"
//    width: 400
    height: window.height*0.9
    antialiasing: true
    id: root
    property int sensorId: 1
    function setSensorId(temp) {sensorId = temp;}

    DateTimeAxis {
        id: axisXTime
        format: "mm:ss"
        tickCount: 6
    }

    ValueAxis {
        id: axisYData
        min: 0
        max: 10
    }

    ValueAxis {
        id: axisYData2
        min: 5
        max: 100
    }

    LineSeries {
        id: lineSeriesTemp
        axisX: axisXTime
        axisYRight: axisYData2
        name: "Temp"
    }

    LineSeries {
        id: lineSeriesRes
        axisX: axisXTime
        axisY: axisYData
        name: "Res"
    }

    Timer {
        id: refreshTimer
        interval: 1000//30 // 60 Hz
        running: true
        repeat: true
        onTriggered: {

            BackEnd.updateChart(lineSeriesTemp, root.sensorId);
            BackEnd.updateChart(lineSeriesRes, root.sensorId);
//            axisXData.min = SensorsList.getSensorXmin();
//            axisXData.max = SensorsList.getSensorXmax();

//            axisYData.min = SensorsList.getSensorYmin();
//            axisYData.max = SensorsList.getSensorYmax();

//            axisZData.min = SensorsList.getSensorZmin();
//            axisZData.max = SensorsList.getSensorZmax();
        }
    }

}
