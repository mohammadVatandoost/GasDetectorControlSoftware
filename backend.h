#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "QDebug"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <iostream>
#include "sensorslist.h"

using namespace std;

struct BoardData {
    float humidityIn = 0;
    float humidityOut = 0;
    float humidityArea = 0 ;
    uint16_t pumpSpeed = 0 ;
    uint8_t batteryCharge = 100;
    bool powerCharge = false;
    bool pumpStatusPower = true;
    bool pumpStatusAirFlow = true;
    float presureSenesor = 0;
    float tempuretureEnv = 0;
    float tempuretureBoard = 0;
    bool fan1 = false;
    bool fan2 = false;
    string time ;
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
    BoardData generalData;

private:
    SensorsList *mList;
signals:

public slots:
private slots:
    void recieveSerialPort();
    void timerSlot();

};

#endif // BACKEND_H
