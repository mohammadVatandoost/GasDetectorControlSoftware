#include "sensorslist.h"

SensorsList::SensorsList()
{
//  Sensor temp1;temp1.tempActive = true; temp1.heaterActive = true;temp1.sensorActive = true;temp1.lowPassFilter = 5;
//  Sensor temp2;
//  Sensor temp3;
//  Sensor temp4;
//  sensorItems.append(temp1);
//  sensorItems.append(temp2);
//  sensorItems.append(temp3);
//  sensorItems.append(temp4);
    if(!QDir("Data").exists()) {
        QDir().mkdir("Data");
    } else {
        cout<<"folderData exits"<<endl;
    }
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

bool SensorsList::isNewId(uint8_t id)
{
    if(id < sensorItems.size()) {
        return false;
    }
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

void SensorsList::setSensorData(SensorPacketRx *data)
{
    sensorItems[data->sensorId].tempLastData =   (float)((float)data->temp/100);
    sensorItems[data->sensorId].current = data->current;
    sensorItems[data->sensorId].res = (float)((float)data->res/100);
    double tempDateTime = QDateTime::currentMSecsSinceEpoch();
    sensorItems[data->sensorId].addResData(tempDateTime, sensorItems[data->sensorId].res);
//    sensorItems[data->sensorId].addResData(tempDateTime, 5);
    sensorItems[data->sensorId].addTempData(tempDateTime, sensorItems[data->sensorId].tempLastData);
//    sensorItems[data->sensorId].addTempData(tempDateTime, 3);
    if(sensorItems[data->sensorId].firstCondition) {
        calculatePPM(data->sensorId);
        emit notifyInfoDataChanged();
    } else {
      sensorItems[data->sensorId].pressure = "DC";
    }
}

void SensorsList::calculatePPM(int sensorId)
{
    Sensor sensor = sensorItems[sensorId];
    float X = sensor.res;
    if(sensor.equation == 0) {
       float sum = sensor.equationE;
       sum = sum + (sensor.equationD*X);
       X = X*sensor.res;
       sum = sum + (sensor.equationC*X);
       X = X*sensor.res;
       sum = sum + (sensor.equationB*X);
       X = X*sensor.res;
       sum = sum + (sensor.equationA*X);
      sensorItems[sensorId].pressure = QString::number(sum);
    } else {
        float sum =  exp(sensor.equationD)*sensor.equationC;
        sum = sum + (exp(sensor.equationB)*sensor.equationA);
        sensorItems[sensorId].pressure = QString::number(sum);
    }
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

void SensorsList::setRtolValue(int sensorId, int configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].Rtol =   static_cast<uint16_t>(configValue);
    } else {
        qDebug() << "sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setTempValue(int sensorId, double configValue)
{
    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId-1].tempSetPoint =   static_cast<float>(configValue);
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
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].recoveryTemp =   static_cast<float>(configValue);
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
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].lowPassFilter;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getR0Value(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].R0;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getRtolValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].Rtol;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getTempValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].tempSetPoint;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getNameValue(int sensorId)
{
    // Ask What Name is
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return 0;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getRecTimeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].recoveryTime;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getRecTempValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].recoveryTemp;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getOPTimeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].operationTime;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getEquationType(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].equation;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getRes(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].res;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getTemp(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].tempLastData;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getCurrent(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].current);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationA(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationA);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationB(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationB);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationC(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationC);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationD(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationD);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationE(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (0 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationE);
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getGasTypeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].gasType;
    } else {
        qDebug() << "Get sensorId not valid :" << sensorId ;
        return "not valid";
    }
}

QString SensorsList::getPressureTypeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].pressureType;
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

