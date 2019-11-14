#include "sensorslist.h"

SensorsList::SensorsList()
{
  Sensor temp1;temp1.tempActive = true; temp1.heaterActive = true;temp1.sensorActive = true;temp1.lowPassFilter = 5;
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
       sensorItems[sensorId-1].lowPassFilter =   static_cast<uint8_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setR0Value(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].R0 =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setRThValue(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].RThereshould =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setTempValue(int sensorId, double configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].tempureture =   static_cast<float>(configValue);
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
       sensorItems[sensorId-1].recoveryTime =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setRecTempValue(int sensorId, double configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].recoveryTemp =   static_cast<float>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setOPTimeValue(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].operationTime =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setGasTypeValue(int sensorId, QString configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].gasType =   configValue;
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setPressureTypeValue(int sensorId, QString configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].pressureType =  configValue;
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationType(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].equation =  static_cast<uint8_t>(configValue) ;
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationA(int sensorId, QString configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].equationA =  configValue.toFloat();
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationB(int sensorId, QString configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].equationB =  configValue.toFloat();
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationC(int sensorId, QString configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].equationC =  configValue.toFloat();
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationD(int sensorId, QString configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].equationD =  configValue.toFloat();
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationE(int sensorId, QString configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].equationE =  configValue.toFloat();
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

int SensorsList::getFilterValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].lowPassFilter;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getR0Value(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].R0;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getRThValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].RThereshould;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getTempValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].tempureture;
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
        return sensorItems[sensorId-1].recoveryTime;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getRecTempValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].recoveryTemp;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getOPTimeValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].operationTime;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getEquationType(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (0 < sensorId) ) {
        return sensorItems[sensorId-1].equation;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationA(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (0 < sensorId) ) {
        return QString::number(sensorItems[sensorId-1].equationA);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationB(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (0 < sensorId) ) {
        return QString::number(sensorItems[sensorId-1].equationB);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationC(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (0 < sensorId) ) {
        return QString::number(sensorItems[sensorId-1].equationC);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationD(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (0 < sensorId) ) {
        return QString::number(sensorItems[sensorId-1].equationD);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationE(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (0 < sensorId) ) {
        return QString::number(sensorItems[sensorId-1].equationE);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getGasTypeValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].gasType;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return "not valid";
    }
}

QString SensorsList::getPressureTypeValue(int sensorId)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId-1].pressureType;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return "not valid";
    }
}

//QVector<double> SensorsList::getEquationCoefficient(int sensorId)
//{
//    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
//        return sensorItems[sensorId-1].equationCoefficient;
//    } else {
//        qDebug() << "Get sensorId not valid :" << sensorId ;
//        QVector<double> temp;
//        return temp;
//    }
//}

//QVector<double> SensorsList::getEquationPowers(int sensorId)
//{
//    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
//        return sensorItems[sensorId-1].equationPower;
//    } else {
//        qDebug() << "Get sensorId not valid :" << sensorId ;
//        QVector<double> temp;
//        return temp;
//    }
//}

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

