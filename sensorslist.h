#ifndef SENSORSLIST_H
#define SENSORSLIST_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "sensor.h"

//struct Sensor {
//    float tempureture = 0;
//    float res = 0;
//    uint8_t current = 0;
//    uint8_t lowPassFilter = 1;
//    uint16_t R0 = 0; // for alghoritm
//    uint16_t RThereshould = 0 ;
//    uint16_t operationTime = 1 ;
//    uint16_t recoveryTime = 1 ;
//    float operationTemp = 0;
//    float recoveryTemp = 0;
//    float tempuretureTh = 0 ; // for T1 in page 1
//    GasKind gasType = GasKind::NO;
//    ValueType type = ValueType::PPM;
//    FormulType equation = FormulType::first;
//    bool RtoR0OrRtoDeltaR = true;
//    bool tempActive = false;
//    bool heaterActive = false;
//    bool sensorActive = false;
//};
class SensorsList : public QObject
{
    Q_OBJECT
public:
    SensorsList();
    bool setSensorItem(int index,Sensor &sensor);
    QVector<Sensor> items();
    QVector<Sensor> sensorItems;
    void addSensor(Sensor newSensor);
    Q_INVOKABLE void setFilterValue(int sensorId, int configValue);
    Q_INVOKABLE void setR0Value(int sensorId, int configValue);
    Q_INVOKABLE void setRThValue(int sensorId, int configValue);
    Q_INVOKABLE void setTempValue(int sensorId, double configValue);
    Q_INVOKABLE void setNameValue(int sensorId, int configValue);
    Q_INVOKABLE void setRecTimeValue(int sensorId, int configValue);
    Q_INVOKABLE void setRecTempValue(int sensorId, double configValue);
    Q_INVOKABLE void setOPTimeValue(int sensorId, int configValue);
    Q_INVOKABLE void setGasTypeValue(int sensorId, QString configValue);

    Q_INVOKABLE int getFilterValue(int sensorId);
    Q_INVOKABLE int getR0Value(int sensorId);
    Q_INVOKABLE int getRThValue(int sensorId);
    Q_INVOKABLE double getTempValue(int sensorId);
    Q_INVOKABLE int getNameValue(int sensorId);
    Q_INVOKABLE int getRecTimeValue(int sensorId);
    Q_INVOKABLE double getRecTempValue(int sensorId);
    Q_INVOKABLE int getOPTimeValue(int sensorId);
    Q_INVOKABLE QString getGasTypeValue(int sensorId);
signals:
   void preItemAppended();
   void postItemAppended();

   void preItemRemoved(int index);
   void postItemRemoved();

public slots:
    void appendItem(); //Sensor sensorItem
    void removeItem(int index);
private:
};

#endif // SENSORSLIST_H
