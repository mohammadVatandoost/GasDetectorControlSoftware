#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include "backend.h"

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)
Q_DECLARE_METATYPE(QDateTimeAxis *)

Backend::Backend(QObject *parent) : QObject(parent)
{
//    createTable();
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

void Backend::setDataBase(DataBase *dataBase)
{
    db = dataBase;
    createTable();
}

bool Backend::checkAlgohoritmFirstCondition(int sensorId)
{
    // check pump
    if(generalData.flowErrorStatus || generalData.electricalErrorStatus) {
       cout<< "checkAlgohoritmFirstCondition:"<< sensorId<< ", flowErrorStatus:"<< generalData.flowErrorStatus << ", electricalErrorStatus:"<<generalData.electricalErrorStatus<<endl;
       alghoritmStop(sensorId);
    }
    Sensor sensor = mList->items()[sensorId];
    // check heater
    if(sensor.tempLastData == HeaterNotActive) {
        mList->sensorItems[sensorId].heaterActive = false;
         alghoritmStop(sensorId);
    } else {
        mList->sensorItems[sensorId].heaterActive = true;
    }
    // check Temperature
    float setPointTemp = sensor.operationTemp ;
    if(sensor.secondCondition) {
        setPointTemp = sensor.recoveryTemp ;
    }

    if( ( (setPointTemp-sensor.tempuretureTh) < sensor.tempLastData ) &&
            (sensor.tempLastData < (setPointTemp+sensor.tempuretureTh) )  ) {
        mList->sensorItems[sensorId].tempActive = true;
    }

    // check Res
    if(!sensor.secondCondition && (mList->sensorItems[sensorId].tempActive || mList->sensorItems[sensorId].firstCondition)) {
        double rMax = 0;
        double rMin = 0;
        double Ravg = calculateRavg(sensorId, &rMax, &rMin);
        cout<< "Ravg: "<< Ravg<<", rMax:"<< rMax << ", rMin:"<< rMin<< ", Rtol * Ravg/100:"<< mList->items()[sensorId].Rtol * Ravg/100 << endl;
//        if(!mList->sensorItems[sensorId].firstCondition) {
           if( ((rMax - rMin)/2) < ( mList->items()[sensorId].Rtol * Ravg/100 ) ) {
              cout<< "*************** Ravg ok first condtion true ***************"<< endl;
              if(!mList->sensorItems[sensorId].firstCondition) {
                  mList->sensorItems[sensorId].timeCounter = 0;
                  mList->sensorItems[sensorId].R0 = static_cast<uint16_t>(Ravg)  ;
              }
              mList->sensorItems[sensorId].firstCondition = true;
              mList->sensorItems[sensorId].sensorActive = true;
           } else {
              mList->sensorItems[sensorId].sensorActive = false;
           }

           if( ( (sensor.res-Ravg) > (sensor.Rtol*Ravg/100) ) && !sensor.r0Check ) {
              mList->sensorItems[sensorId].R0 = (1+sensor.Rtol)*Ravg ;
              mList->sensorItems[sensorId].r0Check = true;
              cout<< "(sensor.res-Ravg) > (sensor.Rtol*Ravg/100) :"<< mList->sensorItems[sensorId].R0<< endl;
           }
           if( ( (Ravg-sensor.res) < (sensor.Rtol*Ravg/100) ) && !sensor.r0Check ) {
              mList->sensorItems[sensorId].R0 = (1- (sensor.Rtol/100) )*Ravg ;
              mList->sensorItems[sensorId].r0Check = true;
              cout<< "(Ravg-sensor.res) < (sensor.Rtol*Ravg/100) :"<< mList->sensorItems[sensorId].R0<< endl;
           }

//        } else {

//        }
    }
//    const int tempSensorId = sensorId;
//    QABSt
//    emit mList->setData(tempSensorId, heaterActive, mList->sensorItems[sensorId].heaterActive);
//    emit mList->notifyInfoDataChanged();
//    emit mList->postItemRemoved();
    return true;
}

uint16_t Backend::filterRes(int sensorId)
{
    return 0;
}

float Backend::calculateRavg(int sensorId, double *rMax, double *rMin)
{
    int tRtol = mList->items()[sensorId].TRtol;
    int resDataSize = mList->items()[sensorId].resData.size();
    double sum = 0;
    if(tRtol > resDataSize) {
        tRtol = resDataSize;
    }
    cout<< "calculateRavg tRtol:"<< tRtol<<endl;
//    cout<< mList->sensorItems[sensorId].resData[resDataSize-1].y() << endl;
    *rMax = 0 ; // mList->sensorItems[sensorId].resData[resDataSize-1].y();
//    cout<< "bugPoint"<<endl;
    *rMin = 1000000; // mList->sensorItems[sensorId].resData[resDataSize-1].y();
//    cout<< "calculateRavg tRtol:"<< tRtol<< ", rMax:"<<*rMax<<", rMin:"<<*rMin<<endl;
    int tRtolTher = resDataSize-tRtol-1;
    for(int i=resDataSize-1; i>tRtolTher; i--) {
        double temp = mList->items()[sensorId].resData[i].y();
        if(temp < *rMin) {
            *rMin = temp;
        }
        if( temp > *rMax) {
            *rMax = temp ;
        }
       sum = temp  + sum ;
    }

    return (sum/tRtol);
}

void Backend::alghoritmStop(int sensorId)
{
    mList->sensorItems[sensorId].alghoritmRunning = false;
    mList->sensorItems[sensorId].firstCondition = false;
    mList->sensorItems[sensorId].secondCondition = false;
    mList->sensorItems[sensorId].timeCounter = 0;
    mList->sensorItems[sensorId].progressValue = 0;
    mList->sensorItems[sensorId].r0Check = false;
    mList->sensorItems[sensorId].heaterActive = false ;
    mList->sensorItems[sensorId].sensorActive = false ;
    mList->sensorItems[sensorId].tempActive = false ;
//    emit mList->notifyInfoDataChanged();
    for(int i=0; i<mList->sensorItems.size(); i++) {
        if(mList->items()[i].alghoritmRunning) {
            return;
        }
    }
    sendPumpSpeedZero = true;
}

void Backend::setPumpValue(int configValue)
{
   generalData.pumpSpeed = static_cast<uint16_t>(configValue);
//   jsonStoring.storeBoardData(generalData);
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
   cout<<"startSensor :"<<sensorId<<endl;
   mList->sensorItems[sensorId].alghoritmRunning = !mList->sensorItems[sensorId].alghoritmRunning;
   if(mList->sensorItems[sensorId].alghoritmRunning) {
      sendPumpSpeedZero = false;
      cout<<"algorithm run:"<< sensorId << ": "<<mList->sensorItems[sensorId].alghoritmRunning<< endl;
   } else {
       alghoritmStop(sensorId);
   }
}

void Backend::startAllSensor()
{
    for(int i=0; i<mList->sensorItems.size(); i++) {
       startSensor(i);
    }
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
           temp.tempSetPoint = mList->items()[sensorId].operationTemp;
       }
     checkAlgohoritmFirstCondition(sensorId);
   } else if(mList->items()[sensorId].heaterStart) {
       temp.tempSetPoint = mList->items()[sensorId].operationTemp;
//       cout<<sensorId <<" heaterStart "<<endl;
   } else if(mList->items()[sensorId].recStart) {
       temp.tempSetPoint = mList->items()[sensorId].recoveryTemp;
//        cout<<sensorId <<" recovery start " << temp.tempSetPoint  <<endl;
   } else {
      temp.tempSetPoint = 0;
   }
//   temp.tempSetPoint = 40;
//   temp.tempSetPoint = 305;
//   cout<< "sendSensorData :"<<unsigned(sensorId)<< ", "<< temp.tempSetPoint << endl;
   uint32_t sum= 0;
//   cout<< "sendSensprData "<< unsigned(sensorId) << " : "<< temp.tempSetPoint  << endl;
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
    mList->sensorItems[sensorId].heaterStart = true;
    mList->sensorItems[sensorId].recStart = false;
    cout<< "sendSensorDataHeater :" << unsigned(sensorId) << ", "<<mList->sensorItems[sensorId].heaterStart<< ", "<<mList->sensorItems[sensorId].recStart<<endl;
}

void Backend::setAxisXTime(QDateTimeAxis *axis)
{
    cout<< "**************set axis time" ;
    axisXTime = axis;
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

void Backend::openKeyboard()
{
//    system("onboard &");
}

void Backend::sendSensorDataRec(int sensorId)
{
    mList->sensorItems[sensorId].heaterStart = false;
    mList->sensorItems[sensorId].recStart = true;
}

void Backend::turnOffHeater(int sensorId)
{
    mList->sensorItems[sensorId].heaterStart = false;
    mList->sensorItems[sensorId].recStart = false;
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
       Sensor temp = getSeneorDataFromDB(m);
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
    if(m->electricalErrorStatus > 0) {
        generalData.electricalErrorStatus = true;
    } else {
        generalData.electricalErrorStatus = false;
    }
    if(m->flowErrorStatus > 0) {
        generalData.flowErrorStatus = true;
    } else {
        generalData.flowErrorStatus = false;
    }
    generalData.fan1 = m->fan1;
    generalData.fan2 = m->fan2;
    generalData.chargingStatus = m->powerCharge;
    generalData.presureSenesor = m->pressureSensor;
    generalData.pumpSpeed = m->pumpSpeed;
    generalData.tempuretureArea = m->tempArea;
    generalData.tempuretureBoard = m->tempBoard;
//    cout<< "getGeneralData:"<<unsigned( m->electricalErrorStatus)<<", "<<unsigned(m->flowErrorStatus)<< endl;
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
    if( db->openConnection() ) {
        SensorSchema sensorSchema;
        if(db->createTable(sensorSchema)) {
            cout<< "table created successfully" << endl;
        }
    }
}

Sensor Backend::getSeneorDataFromDB(SensorPacketRx *m)
{
    if(!db->isOpen) {
       db->openConnection();
    }
    SensorSchema sensorSchema;
    Sensor temp  ;
    if(!db->findById(sensorSchema.getSqlFindById(m->sensorId), &temp)) {
        cout<<"getSeneorDataFromDB "<< unsigned( m->sensorId ) << " not finded"<<endl;
        temp.sensorId = m->sensorId;
        temp.tempLastData = m->temp;
        temp.res = m->res;
        temp.current = m->current;
        sensorSchema.setSensorInfo(temp);
        db->insert(sensorSchema.getSqlInsertCommand());
    } else {
       cout<<"getSeneorDataFromDB "<< unsigned(m->sensorId) << " finded"<<endl;
    }
    return temp;
}

void Backend::updateChart(QAbstractSeries *chartSeries, int sensorId)
{
    if(sensorId < mList->items().size() && -1 < sensorId) {
      if (chartSeries) {
          if(axisXTime) {
  //            cout<< "set axis time" ;
              axisXTime->setMin(QDateTime::fromMSecsSinceEpoch(QDateTime::currentDateTime().toMSecsSinceEpoch()-60000));
              axisXTime->setMax(QDateTime::currentDateTime());
          }
  //         QVector<Sensor> sensors = mList->items();
  //        cout<< "chart update sensor id:"<< sensorId << " points size:"<< mList->sensorItems[sensorId].tempData.size();
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
                   cout << " portName : " << port.portName().toStdString();
        }
        if(serial->open(QIODevice::ReadWrite)) {
          connectState = true; cout << " conndected : ";
          connect(serial, SIGNAL(readyRead()), this, SLOT(recieveSerialPort()));
        } else {
            connectState = false; cout << "Not conndected : ";
            serial->close();
        }
    } else {
//        sendGeneralData();
        if(mList->sensorItems.size()>0) { // if just for test
        for(int i=0; i<mList->sensorItems.size(); i++) {
            if(mList->sensorItems[i].firstCondition) {
                mList->sensorItems[i].timeCounter++;
                if(mList->sensorItems[i].secondCondition) {
                    if(mList->sensorItems[i].timeCounter >= (mList->sensorItems[i].recoveryTime*60)) {
                        cout<< i<< "*********** recovery time finished *************"<<endl;
                        alghoritmStop(i);
                    }
                } else if(mList->sensorItems[i].timeCounter >= (mList->sensorItems[i].operationTime*60)) {
                    cout<< i<< "************** operation time finished *****************"<<endl;
                    mList->sensorItems[i].secondCondition = true;
                    mList->sensorItems[i].sensorActive = false;
                    mList->sensorItems[i].timeCounter = 0;
                    mList->sensorItems[i].progressValue = 1;
                } else {
                    mList->sensorItems[i].progressValue = (float)((float)mList->sensorItems[i].timeCounter / (float)(mList->sensorItems[i].operationTime*60));
                    cout<< i<< "********** progressValue **********:"<< mList->sensorItems[i].progressValue <<endl;
                }
            }
            sendSensorData(i);
         }
//         emit mList->notifyInfoDataChanged();
        }
    }
   } else {
       serial->close();
//       mList->sensorItems[0].tempActive = !mList->sensorItems[0].tempActive;
//       mList->sensorItems[0].sensorActive = !mList->sensorItems[0].sensorActive;
//       mList->sensorItems[0].heaterActive = !mList->sensorItems[0].heaterActive;
//       mList->sensorItems[0].alghoritmRunning = !mList->sensorItems[0].alghoritmRunning;
//       connectState = false;cout << "Disconndected : ";
   }

//   emit notifyInfoDataChanged();
}
