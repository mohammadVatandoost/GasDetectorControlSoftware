#ifndef SENSOR_H
#define SENSOR_H
#include <iostream>
#include <QString>
#include <QVector>
#include <QVector2D>
#include <QPointF>
#include "myutitlity.h"

#define saveToFile  1000

using namespace std;

enum FormulType{ first, second, third };
enum ValueType{ PPM, PDB };
//enum GasKind{ NO, CO, SO2, O2, BTEX, VOC};
enum SensorProperty{
  operationTemp, res, current, lowPassFilter, R0,
  Rtol, operationTime, recoveryTime, recoveryTemp,
  gasType, pressureType, equation, RtoR0OrRtoDeltaR, tempActive, heaterActive, sensorActive, alghoritmRunning,
  pressure, progressValue
};

struct Sensor {
//    float tempSetPoint = 36;
    float tempLastData = 0;
    float res = 0;
    float x = 0;
    uint8_t current = 0;
    uint8_t lowPassFilter = 0;  // divide 10
    uint16_t R0 = 0; // for alghoritm
    float Rtol = 3 ; // percent
    uint16_t TRtol = 120 ; //  second
    uint16_t operationTime = 10 ; // minute
    uint16_t recoveryTime = 5 ; // minute
    float operationTemp = 250;
    float recoveryTemp = 300;
    float tempuretureTh = 5 ; // for T1 in page 1
    QString gasType = "NO";
    QString pressureType = "PPM";
    QString pressure = "DC";
    uint8_t equation = 0;
    float equationA = 1;
    float equationB = 2;
    float equationC = 2;
    float equationD = 2;
    float equationE = 2;
    bool RtoR0OrRtoDeltaR = true;
    bool tempActive = false;
    bool heaterActive = false;
    bool sensorActive = false;
    bool heaterStart = false;
    bool recStart = false;
    int sensorId;
    QVector<QPointF> tempData;
    QVector<QPointF> resData;
    double progressValue = 0;
    // for alghoritm
    bool alghoritmRunning = false;
    bool firstCondition = false; // start operation time
    bool secondCondition = false; // start recovery time
    bool r0Check = false; // start recovery time
    uint16_t timeCounter = 0;
    int minTemp = 0;
    int maxTemp = 400;
    int minRes = 0 ;
    int maxRes = 400;
    uint8_t xType = 0;
    void addTempData(double time, double value) {
        QPointF temp(time,value);
        tempData.append(temp);
        if(tempData.size() > saveToFile*2) {
            cout<< "store to csv file"<<endl;
            saveSensorDataToCSVFile(&tempData, sensorId, "temp", saveToFile);
        }
    }

    void addResData(double time, double value) {
        QPointF temp(time,value);
        resData.append(temp);
        if(resData.size() > saveToFile*2) {
            cout<< "store to csv file"<<endl;
            saveSensorDataToCSVFile(&resData, sensorId, "res", saveToFile);
        }
    }
};



#endif // SENSOR_H
