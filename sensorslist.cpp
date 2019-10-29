#include "sensorslist.h"

SensorsList::SensorsList()
{
  Sensor temp1;temp1.tempActive = true; temp1.heaterActive = true;temp1.sensorActive = true;
  Sensor temp2;
  Sensor temp3;
  Sensor temp4;
  sensorItems.append(temp1);
  sensorItems.append(temp2);
  sensorItems.append(temp3);
  sensorItems.append(temp4);
}

bool SensorsList::setSensorItem(int index, Sensor &sensor)
{
    if(index <0 || index >= sensorItems.size())
        return false;
//    const Sensor oldItem = sensorItems.at(index);
//    if(item.done == oldItem.done && item.description == oldItem.description)
//        return false;
    sensorItems[index] = sensor;
    return true;
}

QVector<Sensor> SensorsList::items()
{
    return sensorItems;
}

void SensorsList::addSensor(Sensor newSensor)
{
    emit preItemAppended();
    sensorItems.append(newSensor);
    emit postItemAppended();
}

void SensorsList::setFilterValue(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].lowPassFilter =   static_cast<uint8_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setR0Value(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].R0 =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setRThValue(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].RThereshould =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setTempValue(int sensorId, double configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].tempureture =   static_cast<float>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setNameValue(int sensorId, int configValue)
{
   // Ask what is It
}

void SensorsList::setRecTimeValue(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].recoveryTime =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setRecTempValue(int sensorId, double configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].recoveryTemp =   static_cast<float>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setOPTimeValue(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].operationTime =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

int SensorsList::getFilterValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].lowPassFilter;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getR0Value(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].R0;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getRThValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].RThereshould;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getTempValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].tempureture;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getNameValue(int sensorId)
{
    // Ask What Name is
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return 0;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getRecTimeValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].recoveryTime;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getRecTempValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].recoveryTemp;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getOPTimeValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].operationTime;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

void SensorsList::appendItem()
{
    emit preItemAppended();

//    Sensor sensorItem;
//    sensorItems.append(sensorItem);
    emit postItemAppended();
}

void SensorsList::removeItem(int index)
{
    emit preItemRemoved(index);
    sensorItems.removeAt(index);
    emit postItemRemoved();
}

