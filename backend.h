﻿#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "QDebug"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <iostream>
#include <QtCharts/QAbstractSeries>
#include <QTime>
#include <QtCharts/QDateTimeAxis>
#include <thread>

//#include
#include "sensorslist.h"
#include "database.h"
#include "sensorschema.h"
#include "packet.h"
#include "jsonstoring.h"



#define tempNotValid 4000
#define heaterNotValid 0

// test this
#pragma pack(push, 1)

using namespace std;

QT_CHARTS_USE_NAMESPACE


class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE void setSensorsList(SensorsList *sensorsList);
    Q_INVOKABLE void setDataBase(DataBase *dataBase);
    QSerialPort *serial;
    QString come_port;
    QTimer *timer;
    BoardData generalData;
    bool sendPumpSpeedZero = true;
    bool connectState = false;
    QByteArray dataBuf;
    uint16_t recieveState = 0;
//    DataBase db{"dataBase"};
    DataBase *db;
    uint16_t packetSize = 0;
    JsonStoring jsonStoring;
    // for chart
    QDateTimeAxis *axisXTime;
    int tempMin = 0;
    int tempMax = 100;
    int resMin = 0;
    int resMax = 100;
    // for alghoritm
    Q_INVOKABLE void startSensor(int sensorId);
    Q_INVOKABLE void startAllSensor();
    bool checkAlgohoritmFirstCondition(int sensorId);
    uint16_t filterRes(int sensorId);
    float calculateRavg(int sensorId, double *rMax, double *rMin);
    void alghoritmStop(int sensorId);

    Q_INVOKABLE void setPumpValue(int configValue);
    Q_INVOKABLE int getPumpValue();
    Q_INVOKABLE bool getPumpStatus();
    Q_INVOKABLE int getHumidityIn();
    Q_INVOKABLE int getHumidityOut();
    Q_INVOKABLE int getHumidityArea();
    Q_INVOKABLE double getTempArea();
    Q_INVOKABLE double getPresureArea();
    Q_INVOKABLE bool getFlowErrorStatus();
    Q_INVOKABLE bool getElectricalErrorStatus();
    Q_INVOKABLE bool getChargingStatus();
    Q_INVOKABLE QString getBatteryCharge();

    void sendSensorData(uint8_t sensorId);
    Q_INVOKABLE void sendSensorDataHeater(int sensorId);
    Q_INVOKABLE void sendSensorDataRec(int sensorId);
    Q_INVOKABLE void turnOffHeater(int sensorId);
    void sendGeneralData();
    void sendPacket(char* data, int size);

    void getSensorData(QByteArray data);
    void getGeneralData(QByteArray data);
    void decodePacket(QByteArray data);
    void createTable();
    Sensor getSeneorDataFromDB(SensorPacketRx *m);

    Q_INVOKABLE int getSensorTempMin();
    Q_INVOKABLE int getSensorTempMax();
    Q_INVOKABLE int getSensorResMin();
    Q_INVOKABLE int getSensorResMax();
    Q_INVOKABLE void openKeyboard();

    QVector<QPointF> testChart;

private:
    SensorsList *mList;
signals:
    void notifyInfoDataChanged();

public slots:
    void updateChart(QAbstractSeries *chartSeries, int sensorId);
    void setAxisXTime(QDateTimeAxis *axis);

private slots:
    void recieveSerialPort();
    void timerSlot();

};

#endif // BACKEND_H
