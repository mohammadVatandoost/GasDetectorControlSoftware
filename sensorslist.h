#ifndef SENSORSLIST_H
#define SENSORSLIST_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QDate>
#include <QDir>
#include <QAbstractListModel>
#include <QModelIndex>
#include <math.h>
#include "sensor.h"
#include "packet.h"
#include "database.h"
#include "sensorschema.h"
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
    Q_INVOKABLE void setDataBase(DataBase *dataBase);
    DataBase *db;
    bool isNewId(uint8_t id);
    QVector<Sensor> items();
    QVector<Sensor> sensorItems;
    void addSensor(Sensor newSensor);
    void setSensorData(SensorPacketRx *data);

    // for alghoritm
    void calculatePPM(int sensorId);

    Q_INVOKABLE void setFilterValue(int sensorId, int configValue);
    Q_INVOKABLE void setR0Value(int sensorId, int configValue);
    Q_INVOKABLE void setRtolValue(int sensorId, int configValue);
    Q_INVOKABLE void setOperationTempValue(int sensorId, double configValue);
    Q_INVOKABLE void setTRtolValue(int sensorId, int configValue);
    Q_INVOKABLE void setRecTimeValue(int sensorId, int configValue);
    Q_INVOKABLE void setRecTempValue(int sensorId, double configValue);
    Q_INVOKABLE void setOPTimeValue(int sensorId, int configValue);
    Q_INVOKABLE void setGasTypeValue(int sensorId, QString configValue);
    Q_INVOKABLE void setPressureTypeValue(int sensorId, QString configValue);
    Q_INVOKABLE void setEquationType(int sensorId, int configValue);
    Q_INVOKABLE void setEquationA(int sensorId, QString configValue);
    Q_INVOKABLE void setEquationB(int sensorId, QString configValue);
    Q_INVOKABLE void setEquationC(int sensorId, QString configValue);
    Q_INVOKABLE void setEquationD(int sensorId, QString configValue);
    Q_INVOKABLE void setEquationE(int sensorId, QString configValue);
    Q_INVOKABLE void setXType(int sensorId, int configValue);

    Q_INVOKABLE int getFilterValue(int sensorId);
    Q_INVOKABLE int getR0Value(int sensorId);
    Q_INVOKABLE int getRtolValue(int sensorId);
    Q_INVOKABLE double getOperationTempValue(int sensorId);
    Q_INVOKABLE int getTRtolValue(int sensorId);
    Q_INVOKABLE int getRecTimeValue(int sensorId);
    Q_INVOKABLE double getRecTempValue(int sensorId);
    Q_INVOKABLE int getOPTimeValue(int sensorId);
    Q_INVOKABLE int getEquationType(int sensorId);
    Q_INVOKABLE double getRes(int sensorId);
    Q_INVOKABLE double getTemp(int sensorId);
    Q_INVOKABLE QString getCurrent(int sensorId);
    Q_INVOKABLE QString getEquationA(int sensorId);
    Q_INVOKABLE QString getEquationB(int sensorId);
    Q_INVOKABLE QString getEquationC(int sensorId);
    Q_INVOKABLE QString getEquationD(int sensorId);
    Q_INVOKABLE QString getEquationE(int sensorId);
    Q_INVOKABLE QString getGasTypeValue(int sensorId);
    Q_INVOKABLE QString getPressureTypeValue(int sensorId);
    Q_INVOKABLE QString getPressure(int sensorId);
    Q_INVOKABLE int getXType(int sensorId);
    Q_INVOKABLE double getX(int sensorId);
    Q_INVOKABLE double getProgressValue(int sensorId);
    Q_INVOKABLE int getTempActiveValue(int sensorId);
    Q_INVOKABLE int getHeaterActiveValue(int sensorId);
    Q_INVOKABLE int getSensorActiveValue(int sensorId);
    Q_INVOKABLE int getAlgorithmRunnigValue(int sensorId);

//    Q_INVOKABLE QVector<double> getEquationCoefficient(int sensorId);
//    Q_INVOKABLE QVector<double> getEquationPowers(int sensorId);
    void setHeaterValue(int sensorId, bool value);
signals:
   void preItemAppended();
   void postItemAppended();
   void setData(const QModelIndex &index, const QVariant &value, int role);

   void preItemRemoved(int index);
   void postItemRemoved();
   void notifyInfoDataChanged();
public slots:
    void appendItem(); //Sensor sensorItem
    void removeItem(int index);
private:
};

#endif // SENSORSLIST_H
