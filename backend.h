#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <iostream>

using namespace std;

struct boardData {
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

signals:

public slots:
};

#endif // BACKEND_H
