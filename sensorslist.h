#ifndef SENSORSLIST_H
#define SENSORSLIST_H

#include <QObject>
#include <QVector>
#include "sensor.h"

class SensorsList : public QObject
{
    Q_OBJECT
public:
    SensorsList();
    bool setSensorItem(int index,Sensor &sensor);
    QVector<Sensor> items();
    QVector<Sensor> sensorItems;
    void addSensor(Sensor newSensor);
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
