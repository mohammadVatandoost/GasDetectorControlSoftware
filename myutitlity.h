#ifndef MYUTITLITY_H
#define MYUTITLITY_H

#include <iostream>
#include <sstream>      // std::stringstream
#include <QPointF>
#include <QVector>
#include "csv.h"

using namespace std;

class MyUtitlity {
public:
    MyUtitlity() {}
    string numberToString(double num) {
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(uint8_t num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(uint16_t num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(uint32_t num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(int num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(float num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
};

void saveSensorDataToCSVFile(QVector<QPointF> dataList, int sensorNumber, QString tempOrRes) {
    QVector<QStringList> dataStringList;
    for(int j = 0; j<dataList.length(); j++) {
        QStringList listRow;
        listRow.append( QString::number(dataList[j].x()));
        listRow.append( QString::number(dataList[j].y()));
        dataStringList.append(listRow);
    }
    appendDataToCSV(dataStringList, "./Data/sensor"+QString::number(sensorNumber)+tempOrRes+".csv"); //"_"+QString::number(minuteBuff)+
    dataList.clear();
}

#endif // MYUTITLITY_H
