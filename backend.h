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
#include "database.h"
#include "sensorschema.h"

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

struct SensorPacketTx {
    uint8_t sensorId;
    uint16_t tempSetPoint;
};

struct SensorPacketRx {
    uint8_t sendsorId;
    uint16_t temp;
    uint8_t current;
    uint32_t Res;
};

struct BoardPacketTx {
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
    BoardData generalData;
    bool connectState = false;
    QByteArray dataBuf;
    DataBase db{"dataBase"};

    Q_INVOKABLE void setPumpValue(int configValue);
    Q_INVOKABLE int getPumpValue();
    Q_INVOKABLE bool getPumpStatus();
    Q_INVOKABLE int getHumidityIn();
    Q_INVOKABLE int getHumidityOut();
    Q_INVOKABLE int getHumidityArea();
    Q_INVOKABLE double getTempArea();
    Q_INVOKABLE double getPresureArea();
    Q_INVOKABLE void startSensor(int sensorId);
    Q_INVOKABLE void startAllSensor();

    char* makeSensorData(uint8_t sensorId);
    char* makeGeneralData();
    void sendPacket(char* data, int size);

    void getSensorData(QByteArray data);
    void getGeneralData(QByteArray data);
    void createTable();

private:
    SensorsList *mList;
signals:
    void notifyInfoDataChanged();

public slots:
    void updateChart(QAbstractSeries *chartSeries, int sensorId);
private slots:
    void recieveSerialPort();
    void timerSlot();

};

#endif // BACKEND_H
