#ifndef BACKEND_H
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
#include "sensorslist.h"

using namespace std;

QT_CHARTS_USE_NAMESPACE

struct BoardData {
    uint8_t humidityIn = 0;
    uint8_t humidityOut = 0;
    uint8_t humidityArea = 0 ;
    uint16_t pumpSpeed = 0 ;
    uint8_t batteryCharge = 100;
    bool powerCharge = false;
    bool pumpStatusPower = true;
    bool pumpStatusAirFlow = true;
    float presureSenesor = 0;
    float tempuretureArea = 0;
    float tempuretureBoard = 0;
    bool fan1 = false;
    bool fan2 = false;
    string time ;
};

struct SensorPacketTr {
    uint8_t sensorId;
    uint16_t tempSetPoint;
};

struct SensorPacketRx {
    uint8_t sendsorId;
    uint16_t temp;
    uint8_t current;
    uint32_t Res;
};

struct BoardPacketTr {
    uint8_t pumpSpeed;
};

struct BoardPacketRx {
    uint8_t humidityIn;
    uint8_t humidityOut;
    uint8_t humidityArea;
    uint16_t pumpSpeed;
    uint16_t tempArea;
    uint16_t tempBoard;
    uint8_t pumpStatusPower; // boolean
    uint8_t pumpStatusAirFlow; // boolean
    uint8_t powerCharge;
    uint8_t batteryCharge;
    uint16_t pressureSensor;
    uint8_t fan1; // boolean
    uint8_t fan2; // boolean
};

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE void setSensorsList(SensorsList *sensorsList);
    QSerialPort *serial;
    QString come_port;
    QTimer *timer;
    bool connectState = false;
    Q_INVOKABLE void setPumpValue(int configValue);
    Q_INVOKABLE int getPumpValue();
    BoardData generalData;

    char* makeSensorData(uint8_t sensorId);
    char* makeGeneralData();
    void sendPacket(char* data, int size);

    void getSensorData(QByteArray data);
    void getGeneralData(QByteArray data);

private:
    SensorsList *mList;
signals:

public slots:
    void updateChart(QAbstractSeries *chartSeries, int sensorId);
private slots:
    void recieveSerialPort();
    void timerSlot();

};

#endif // BACKEND_H
