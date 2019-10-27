#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QObject>
#include <QAbstractListModel>
//#include "sensor.h"

class SensorsList;

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SensorsList *list READ list WRITE setList )
public:
    explicit SensorModel(QObject *parent = nullptr);
//    struct Sensor {
//        float tempureture = 0;
//        float res = 0;
//        uint8_t current = 0;
//        uint8_t lowPassFilter = 1;
//        uint16_t R0 = 0; // for alghoritm
//        uint16_t RThereshould = 0 ;
//        uint16_t operationTime = 1 ;
//        uint16_t recoveryTime = 1 ;
//        float operationTemp = 0;
//        float recoveryTemp = 0;
//        float tempuretureTh = 0 ; // for T1 in page 1
//        GasKind gasType = GasKind::NO;
//        ValueType type = ValueType::PPM;
//        FormulType equation = FormulType::first;
//        bool RtoR0OrRtoDeltaR = true;
//        bool tempActive = false;
//        bool heaterActive = false;
//        bool sensorActive = false;
//    };
    enum {
      tempureture, res, current, lowPassFilter, R0,
      RThereshould, operationTime, recoveryTime, recoveryTemp,
      gasType, type, equation, RtoR0OrRtoDeltaR, tempActive, heaterActive, sensorActive
    };
    // Header: int routerNumber = 123;
//    int sensorNumber = 345;
//    QString bordar = "x";
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // for sensorList Q_PROPERTY
    SensorsList *list() const;
    void setList(SensorsList *list);
private:
    SensorsList *mList;
};

#endif // SENSORMODEL_H
