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

void SensorsList::setDataBase(DataBase *dataBase)
{
    db = dataBase;
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
//    cout<< data->sensorId << ":"<<(float)((float)data->temp/100);
    sensorItems[data->sensorId].tempLastData =   (float)((float)data->temp/100);
    sensorItems[data->sensorId].current = data->current;
//    sensorItems[data->sensorId].res = (float)((float)data->res/100);
    double tempDateTime = QDateTime::currentMSecsSinceEpoch();
    sensorItems[data->sensorId].addResData(tempDateTime, (float)((float)data->res/100));
//    sensorItems[data->sensorId].addResData(tempDateTime, 5);
    sensorItems[data->sensorId].addTempData(tempDateTime, sensorItems[data->sensorId].tempLastData);
//    sensorItems[data->sensorId].addTempData(tempDateTime, 3);

//     emit notifyInfoDataChanged();
//    emit postItemAppended();
//    cout << "update pressure changed";
    if(sensorItems[data->sensorId].firstCondition && !sensorItems[data->sensorId].secondCondition) {
        calculatePPM(data->sensorId);
////        calculatePPM(data->sensorId);
////        emit notifyInfoDataChanged();
    }
//    else {

//      sensorItems[data->sensorId].pressure = "DC";
//    }
}

void SensorsList::calculatePPM(int sensorId)
{

    Sensor sensor = sensorItems[sensorId];
    float X = sensor.res /  sensor.R0;
    cout<< "calculatePPM sensorId:"<< sensorId << ", xType:"<< unsigned(sensorItems[sensorId].xType)<< ", equation:"<< unsigned(sensor.equation)<<endl;
    if(sensorItems[sensorId].xType == 1) {
        if(sensor.gasType == "O2") {
           X =  (sensor.res - sensor.R0) / sensor.R0 ;
        } else {
           X =  abs(sensor.res - sensor.R0) / sensor.R0 ;
        }
    }
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
      cout<< "sum :" << sum<< ", "<< sensorItems[sensorId].pressure.toStdString() << ", "<< QString::number(sum).toStdString() <<endl;
    } else {
        float sum =  exp(sensor.equationD)*sensor.equationC;
        sum = sum + (exp(sensor.equationB)*sensor.equationA);
        sensorItems[sensorId].pressure = QString::number(sum);
        cout<< "sum :" << sum << ", "<< sensorItems[sensorId].pressure.toStdString() << ", "<< QString::number(sum).toStdString() <<endl;
    }
}

void SensorsList::setFilterValue(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].lowPassFilter =   static_cast<uint8_t>(configValue);
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setFilterValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setR0Value(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].R0 =   static_cast<uint16_t>(configValue);
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setR0Value sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setRtolValue(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].Rtol =   static_cast<float>(configValue);
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setRtolValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setOperationTempValue(int sensorId, double configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].operationTemp =   static_cast<float>(configValue);
       SensorSchema sensorSchema;
//       cout << sensorItems[sensorId].pressureType << " pressureType " ;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setTempValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setTRtolValue(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].TRtol =   static_cast<uint16_t>(configValue);
       SensorSchema sensorSchema;
//       cout << sensorItems[sensorId].pressureType << " pressureType " ;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setTempValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setRecTimeValue(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].recoveryTime =   static_cast<uint16_t>(configValue);
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setRecTimeValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setRecTempValue(int sensorId, double configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].recoveryTemp =   static_cast<float>(configValue);
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setRecTempValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setOPTimeValue(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].operationTime =   static_cast<uint16_t>(configValue);
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setOPTimeValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setGasTypeValue(int sensorId, QString configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].gasType =   configValue;
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setGasTypeValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setPressureTypeValue(int sensorId, QString configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].pressureType =  configValue;
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setPressureTypeValue sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationType(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].equation =  static_cast<uint8_t>(configValue) ;
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
//       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setEquationType sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationA(int sensorId, QString configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].equationA =  configValue.toFloat();
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
//       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setEquationA sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationB(int sensorId, QString configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].equationB =  configValue.toFloat();
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
//       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setEquationB sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationC(int sensorId, QString configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].equationC =  configValue.toFloat();
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
//       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setEquationC sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationD(int sensorId, QString configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].equationD =  configValue.toFloat();
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
//       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setEquationD sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setEquationE(int sensorId, QString configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].equationE =  configValue.toFloat();
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setEquationE sensorId not valid :" << sensorId ;
    }
}

void SensorsList::setXType(int sensorId, int configValue)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
       sensorItems[sensorId].xType =  configValue;
       SensorSchema sensorSchema;
       sensorSchema.setSensorInfo(sensorItems[sensorId]);
       db->update(sensorSchema.getSqlUpdateCommand(sensorId));
    } else {
        cout << "setXType sensorId not valid :" << sensorId ;
    }
}

int SensorsList::getFilterValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].lowPassFilter;
    } else {
        cout << "getFilterValue Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getR0Value(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].R0;
    } else {
        cout << "getR0Value Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getRtolValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].Rtol;
    } else {
        cout << "getRtolValue Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getOperationTempValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].operationTemp;
    } else {
        cout << "getTempValue Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getTRtolValue(int sensorId)
{
    // Ask What Name is
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].TRtol;
    } else {
        cout << "getNameValue Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getRecTimeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].recoveryTime;
    } else {
        cout << "getRecTimeValue Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getRecTempValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].recoveryTemp;
    } else {
        cout << "getRecTempValue Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getOPTimeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].operationTime;
    } else {
        cout << "getOPTimeValue Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getEquationType(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].equation;
    } else {
        cout << "getEquationType Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getRes(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].res;
    } else {
        cout << "getRes Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getTemp(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].tempLastData;
    } else {
        cout << "getTemp Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getCurrent(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].current);
    } else {
        cout << "getCurrent Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationA(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationA);
    } else {
        cout << "getEquationA Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationB(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationB);
    } else {
        cout << "getEquationB Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationC(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationC);
    } else {
        cout << "getEquationC Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationD(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationD);
    } else {
        cout << "getEquationD Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getEquationE(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return QString::number(sensorItems[sensorId].equationE);
    } else {
        cout << "getEquationE Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

QString SensorsList::getGasTypeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].gasType;
    } else {
        cout << "getGasTypeValue Get sensorId not valid :" << sensorId ;
        return "not valid";
    }
}

QString SensorsList::getPressureTypeValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].pressureType;
    } else {
        cout << "getPressureTypeValue Get sensorId not valid :" << sensorId ;
        return "not valid";
    }
}

QString SensorsList::getPressure(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].pressure;
    } else {
        cout << "getPressure Get sensorId not valid :" << sensorId ;
        return "not valid";
    }
}

int SensorsList::getXType(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].xType;
    } else {
        cout << "getXType Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

double SensorsList::getProgressValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        return sensorItems[sensorId].progressValue;
    } else {
        cout << "getXType Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getTempActiveValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        if(sensorItems[sensorId].tempActive) {
            return 1;
        } else {
            return 0;
        }
    } else {
        cout << "getXType Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getHeaterActiveValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        if(sensorItems[sensorId].heaterActive) {
            return 1;
        } else {
            return 0;
        }
    } else {
        cout << "getXType Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getSensorActiveValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        if(sensorItems[sensorId].sensorActive) {
            return 1;
        } else {
            return 0;
        }
    } else {
        cout << "getXType Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

int SensorsList::getAlgorithmRunnigValue(int sensorId)
{
    if( (sensorId < sensorItems.size()) && (-1 < sensorId) ) {
        if(sensorItems[sensorId].alghoritmRunning) {
            return 1;
        } else {
            return 0;
        }
    } else {
        cout << "getXType Get sensorId not valid :" << sensorId ;
        return 0;
    }
}

void SensorsList::setHeaterValue(int sensorId, bool value)
{

//    emit setData(QModelIndex(sensorId, 2, NULL), heaterActive, value);
}

//QVector<double> SensorsList::getEquationCoefficient(int sensorId)
//{
//    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
//        return sensorItems[sensorId].equationCoefficient;
//    } else {
//        cout << "Get sensorId not valid :" << sensorId ;
//        QVector<double> temp;
//        return temp;
//    }
//}

//QVector<double> SensorsList::getEquationPowers(int sensorId)
//{
//    if( (sensorId <= sensorItems.size()) && (-1 < sensorId) ) {
//        return sensorItems[sensorId].equationPower;
//    } else {
//        cout << "Get sensorId not valid :" << sensorId ;
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

