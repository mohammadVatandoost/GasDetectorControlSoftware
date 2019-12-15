#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include "backend.h"

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)
Q_DECLARE_METATYPE(QDateTimeAxis *)

Backend::Backend(QObject *parent) : QObject(parent)
{
    createTable();
    serial = new QSerialPort(this);
    serial->close();
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    // timer for connection check
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(1000);

    generalData = jsonStoring.getBoardData();
}

void Backend::setSensorsList(SensorsList *sensorsList)
{
    mList = sensorsList;
}

bool Backend::checkAlgohoritmFirstCondition(int sensorId)
{
    if(generalData.flowErrorStatus && generalData.electricalErrorStatus) {
       alghoritmStop(sensorId);
    }
    Sensor sensor = mList->items()[sensorId];
    if(sensor.tempLastData == HeaterNotActive) {
         alghoritmStop(sensorId);
    }
    if( ( (sensor.tempSetPoint-sensor.tempuretureTh) < sensor.tempLastData ) &&
            (sensor.tempLastData < (sensor.tempSetPoint+sensor.tempuretureTh) ) &&
            (!sensor.firstCondition)  ) {
        int *rMax = 0;
        int *rMin = 0;
        double Ravg = calculateRavg(sensorId, rMax, rMin);
        if( (*rMax - *rMin) < (mList->items()[sensorId].R0 * Ravg ) ) {
            mList->items()[sensorId].timeCounter = 0;
            mList->items()[sensorId].firstCondition = true;
        }
    }

    return true;
}

uint16_t Backend::filterRes(int sensorId)
{
    return 0;
}

float Backend::calculateRavg(int sensorId, int *rMax, int *rMin)
{
    int tRtol = mList->items()[sensorId].Rtol;
    double sum = 0;
    if(tRtol < mList->items()[sensorId].resData.size()) {
        tRtol = mList->items()[sensorId].resData.size();
    }
    *rMax = mList->items()[sensorId].resData[mList->items()[sensorId].resData.size()-1].y();
    rMin = rMax;
    for(int i=0; i<tRtol;i++) {
        double temp = mList->items()[sensorId].resData[i].y();
        if(temp < *rMin) {
            *rMin = temp;
        } else if( temp > *rMax) {
            *rMax = temp ;
        }
       sum = temp  + sum ;
    }

    return (sum/tRtol);
}

void Backend::alghoritmStop(int sensorId)
{
    mList->items()[sensorId].alghoritmRunning = false;
    mList->items()[sensorId].firstCondition = false;
    mList->items()[sensorId].secondCondition = false;
    mList->items()[sensorId].timeCounter = 0;
    for(int i=0; i<mList->items().size(); i++) {
        if(mList->items()[i].alghoritmRunning) {
            return;
        }
    }
    sendPumpSpeedZero = true;
}

void Backend::setPumpValue(int configValue)
{
   generalData.pumpSpeed = static_cast<uint16_t>(configValue);
}

int Backend::getPumpValue()
{
    return generalData.pumpSpeed;
}

bool Backend::getPumpStatus()
{
    if(generalData.pumpSpeed == 0) {
        return false;
    } else {
        return true;
    }
}

int Backend::getHumidityIn()
{
    return generalData.humidityIn;
}

int Backend::getHumidityOut()
{
    return generalData.humidityOut;
}

int Backend::getHumidityArea()
{
    return generalData.humidityArea;
}

double Backend::getTempArea()
{
    return generalData.tempuretureArea;
}

double Backend::getPresureArea()
{
    return generalData.presureSenesor;
}

void Backend::startSensor(int sensorId)
{
   mList->items()[sensorId].alghoritmRunning = !mList->items()[sensorId].alghoritmRunning;
   if(mList->items()[sensorId].alghoritmRunning) {
      sendPumpSpeedZero = false;
   } else {
       mList->items()[sensorId].firstCondition = false;
       for(int i=0; i<mList->items().size(); i++) {
           if(mList->items()[i].alghoritmRunning) {
               return;
           }
       }
       sendPumpSpeedZero = true;
   }
}

void Backend::startAllSensor()
{

}

bool Backend::getFlowErrorStatus()
{
    return generalData.flowErrorStatus;
}

bool Backend::getElectricalErrorStatus()
{
    return generalData.electricalErrorStatus;
}

bool Backend::getChargingStatus()
{
    return generalData.chargingStatus;
}

QString Backend::getBatteryCharge()
{
    return QString::number(generalData.batteryCharge)+"%";
}

void Backend::sendSensorData(uint8_t sensorId)
{
//    cout<< "sendSensprData "<<sensorId << endl;
   SensorPacketTx temp;
//   QVector<Sensor> sensors = mList->items();
   temp.sensorId = sensorId;
   if(mList->items()[sensorId].alghoritmRunning) {
       if(mList->sensorItems[sensorId].secondCondition) {
           temp.tempSetPoint = mList->items()[sensorId].recoveryTemp;
       } else if(mList->sensorItems[sensorId].firstCondition) {
           temp.tempSetPoint = mList->items()[sensorId].operationTemp;
       } else {
           temp.tempSetPoint = mList->items()[sensorId].tempSetPoint;
       }
     checkAlgohoritmFirstCondition(sensorId);
   } else if(mList->items()[sensorId].heaterStart) {
       temp.tempSetPoint = mList->items()[sensorId].tempSetPoint;
//       cout<<sensorId <<" heaterStart "<<endl;
   } else if(mList->items()[sensorId].recStart) {
       temp.tempSetPoint = mList->items()[sensorId].recoveryTemp;
//        cout<<sensorId <<" recovery start " << temp.tempSetPoint  <<endl;
   } else {
      temp.tempSetPoint = 100;
   }
   temp.tempSetPoint = 40;
//   temp.tempSetPoint = 305;
   uint32_t sum= 0;

   char* dataBytes = static_cast<char*>(static_cast<void*>(&temp));
   for(int i=1; i<sizeof(struct SensorPacketTx); i++) {
       sum = sum + ((uint8_t)dataBytes[i]);
   }
//   dataBytes[sizeof(struct SensorPacketTx)] = (uint8_t)sum%256;
//   cout<< "sendSensorData:" <<sensorId << " , " << temp.tempSetPoint<< " checksum:"<<unsigned(dataBytes[sizeof(struct SensorPacketTx)])<<endl;
   QString packet = "*@" ;
   QByteArray tx_data; tx_data.append(packet);
   serial->write(tx_data);
   serial->write(dataBytes, sizeof(struct SensorPacketTx));
   uint8_t checkSum= (uint8_t)sum%256;//reinterpret_cast<uint8_t>(sum%256);
   QByteArray checkSumByte;
   checkSumByte.append(checkSum);
   serial->write(checkSumByte);
}

void Backend::sendSensorDataHeater(int sensorId)
{
    mList->sensorItems[sensorId].heaterActive = true;
    mList->sensorItems[sensorId].recStart = false;
}

void Backend::setAxisXTime(QDateTimeAxis *axis)
{
    qDebug()<< "**************set axis time" ;
    axisXTime = axis;
//    qDebug() << "setAxisXTime()" << axisXTime->format();
    axisXTime->setMin(QDateTime::currentDateTime());
    axisXTime->setMax(QDateTime::currentDateTime().addSecs(60));
}

int Backend::getSensorTempMin()
{
    return tempMin;
}

int Backend::getSensorTempMax()
{
    return tempMax;
}

int Backend::getSensorResMin()
{
    return resMin;
}

int Backend::getSensorResMax()
{
    return resMax;
}


void Backend::sendSensorDataRec(int sensorId)
{
    mList->sensorItems[sensorId].heaterActive = false;
    mList->sensorItems[sensorId].recStart = true;
}

void Backend::sendGeneralData()
{
  cout<<"sendGeneralData :"<<endl;
  BoardPacketTx temp;
  if(sendPumpSpeedZero) {
    temp.pumpSpeed = 0;
  } else {
    temp.pumpSpeed = generalData.pumpSpeed;
  }

  uint32_t sum= 0;
  char* dataBytes = static_cast<char*>(static_cast<void*>(&temp));
  for(int i=1; i<sizeof(struct BoardPacketTx); i++) {
      sum = sum + ((uint8_t)dataBytes[i]);
  }
  dataBytes[sizeof(struct BoardPacketTx)] = (uint8_t)sum%256;
  QString packet = "*@" ;
  QByteArray tx_data; tx_data.append(packet);
  serial->write(tx_data);
  serial->write(dataBytes, sizeof(struct BoardPacketTx)+1);
//  delete dataBytes;
}

void Backend::sendPacket(char *data, int size)
{
    serial->write(data);
}

void Backend::getSensorData(QByteArray data)
{
//    cout<< "getSensorData"<<endl;
   if(data.size() == sizeof(struct SensorPacketRx)) {
    SensorPacketRx *m = reinterpret_cast<SensorPacketRx*>(data.data());
    if(mList->isNewId(m->sensorId)) {
       Sensor temp = getSeneorDataFromDB(m->sensorId);
       temp.sensorId = m->sensorId;
       temp.current =  m->current;
       temp.tempLastData = m->temp;
       temp.res = m->res;
       mList->addSensor(temp);
    } else {
        mList->setSensorData(m);
    }

   } else {
       cout<< "getSensorData "<< data.size() << " must be "<<sizeof(struct SensorPacketRx);
   }
}

void Backend::getGeneralData(QByteArray data)
{
//    cout<< "getGeneralData"<<endl;
  if(data.size() == sizeof(struct BoardPacketRx)) {
    BoardPacketRx *m = reinterpret_cast<BoardPacketRx*>(data.data());
    generalData.humidityIn = m->humidityIn;
    generalData.humidityArea = m->humidityArea;
    generalData.humidityOut = m->humidityOut;
    generalData.batteryCharge = m->batteryCharge;
    generalData.electricalErrorStatus = m->electricalErrorStatus;
    generalData.flowErrorStatus = m->flowErrorStatus;
    generalData.fan1 = m->fan1;
    generalData.fan2 = m->fan2;
    generalData.chargingStatus = m->powerCharge;
    generalData.presureSenesor = m->pressureSensor;
    generalData.pumpSpeed = m->pumpSpeed;
    generalData.tempuretureArea = m->tempArea;
    generalData.tempuretureBoard = m->tempBoard;
//    jsonStoring.storeBoardData(generalData);
  } else {
      cout<< "getGeneralData "<< data.size() << " must be "<<sizeof(struct BoardPacketRx);
  }
}

void Backend::decodePacket(QByteArray data)
{
//    cout<< endl << "decodePacket data.size():" << data.size() << " ," ;
    if(data.size() > 2){
//        cout<< ", packetCode :" << unsigned(static_cast<uint8_t>(data[0])) << endl ;
        uint32_t sum=0;
        for(int i=1; i<data.size()-1; i++) {
//            cout<< unsigned(data[i]&0xFF) << ",";
            sum = sum + ((uint8_t)data[i]);
        }
//        cout<<endl;
        if( sum % 256 == ((uint8_t)data[data.size()-1]) ) {
//          cout<< "checksum is correct"<<endl;
          uint8_t packetCode = ((uint8_t)data[0]);
          data.remove(data.size()-1,1);
          data.remove(0,1);
          if(packetCode == SensorDataPacketCodeRx) {
              getSensorData(data);
          } else if (packetCode == BoardDataPacketCodeRx) {
             getGeneralData(data);
          }
        } else {
            cout << unsigned(static_cast<uint8_t>(data[0])) <<", " << unsigned(static_cast<uint8_t>(data[data.size()-1])) << " checsum is wrong " << sum%256  << endl;
        }
    }
}

void Backend::createTable()
{
    if( db.openConnection() ) {
        SensorSchema sensorSchema;
        if(db.createTable(sensorSchema)) {
            cout<< "table created successfully" << endl;
        }
    }
}

Sensor Backend::getSeneorDataFromDB(int sId)
{
    if(!db.isOpen) {
       db.openConnection();
    }
    SensorSchema sensorSchema;
    Sensor temp  ;
    if(!db.findById(sensorSchema.getSqlFindById(sId), &temp)) {
        cout<<"getSeneorDataFromDB "<<sId << " not finded"<<endl;
    } else {
       cout<<"getSeneorDataFromDB "<<sId << " finded"<<endl;
    }
    return temp;
}

void Backend::updateChart(QAbstractSeries *chartSeries, int sensorId)
{
  if(sensorId < mList->items().size() && -1 < sensorId) { 
    if (chartSeries) {
        if(axisXTime) {
//            qDebug()<< "set axis time" ;
            axisXTime->setMin(QDateTime::fromMSecsSinceEpoch(QDateTime::currentDateTime().toMSecsSinceEpoch()-60000));
            axisXTime->setMax(QDateTime::currentDateTime());
        }
//         QVector<Sensor> sensors = mList->items();
        qDebug()<< "chart update sensor id:"<< sensorId << " points size:"<< mList->sensorItems[sensorId].tempData.size();
        QXYSeries *xySeries = static_cast<QXYSeries *>(chartSeries);

        if(chartSeries->name() == "Temp") {
          QVector<QPointF> points = mList->sensorItems[sensorId].tempData;
          xySeries->replace(points);
        } else {
            QVector<QPointF> points = mList->sensorItems[sensorId].resData;
            xySeries->replace(points);
        }
    }
  }
}

void Backend::recieveSerialPort()
{
    QByteArray data;
    data = serial->readAll();
//    cout<< "recieveSerialPort:";
    for(int i=0; i< data.size(); i++) {
//        cout<< data[i] << "|"<< ((uint16_t)data[i]) << ",";
        if(data[i] == '*' && recieveState == 0) {
            recieveState = recieveState + 1;
            decodePacket(dataBuf);
        } else if( recieveState == 1) {
            if(data[i] == '@') {
              recieveState = recieveState + 1;
            } else {
                recieveState = 0;
            }
            dataBuf.clear();
        } else if(recieveState == 2) {
            uint8_t packetCode = static_cast<uint8_t>(data[i]);
            if(packetCode == SensorDataPacketCodeRx) {
                packetSize =  sizeof(struct SensorPacketRx);
                dataBuf.append(data[i]);
                recieveState = recieveState + 1;
            } else if(packetCode == BoardDataPacketCodeRx) {
                packetSize =  sizeof(struct BoardPacketRx);
                dataBuf.append(data[i]);
                recieveState = recieveState + 1;
            } else {
                packetSize = 0;
                recieveState = 0;
                dataBuf.clear();
            }
//            cout <<"packetCode :"<< unsigned(packetCode) << ", packetSize :" << packetSize<<endl  ;

        } else if(recieveState > 2){
            dataBuf.append(data[i]);
            recieveState = recieveState + 1;
//            cout<< "rs:"<<recieveState << ":" <<data[i] <<",";
            if( packetSize + 3 < recieveState) {
               recieveState = 0;
            }
        }
    }
//    cout<<endl;
}

void Backend::timerSlot()
{
   if(QSerialPortInfo::availablePorts().size()>0) {
    if(!serial->isOpen()) {
        Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
                   serial->setPortName(port.portName());
                   qDebug() << " portName : " << port.portName();
        }
        if(serial->open(QIODevice::ReadWrite)) {
          connectState = true; qDebug() << " conndected : ";
          connect(serial, SIGNAL(readyRead()), this, SLOT(recieveSerialPort()));
        } else {
            connectState = false; qDebug() << "Not conndected : ";
            serial->close();
        }
    } else {
//        sendGeneralData();
        if(mList->sensorItems.size()>0) {
        for(int i=0; i<1; i++) {
            if(mList->sensorItems[i].firstCondition) {
                mList->sensorItems[i].timeCounter++;
                if(mList->sensorItems[i].secondCondition) {
                    if(mList->sensorItems[i].timeCounter >= mList->sensorItems[i].operationTime) {
                        alghoritmStop(i);
                    }
                } else if(mList->sensorItems[i].timeCounter >= mList->sensorItems[i].recoveryTime) {
                    mList->sensorItems[i].secondCondition = true;
                    mList->sensorItems[i].timeCounter = 0;
                }
            }
            sendSensorData(i);
        }
        }
    }
   } else {
       serial->close();
//       connectState = false;qDebug() << "Disconndected : ";
   }

//   emit notifyInfoDataChanged();
}
