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

struct Sensor {
    float tempSetPoint = 0;
    float tempLastData = 0;
    float res = 0;
    uint8_t current = 0;
    uint8_t lowPassFilter = 1;
    uint16_t R0 = 0; // for alghoritm
    uint16_t RThereshould = 0 ;
    uint16_t operationTime = 1 ;
    uint16_t recoveryTime = 1 ;
    float operationTemp = 0;
    float recoveryTemp = 0;
    float tempuretureTh = 0 ; // for T1 in page 1
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
    // for alghoritm
    bool alghoritmRunning = false;
    bool firstCondition = false; // for tempuretureTh range
    bool secondCondition = false;
    uint16_t timeCounter = 0;

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
