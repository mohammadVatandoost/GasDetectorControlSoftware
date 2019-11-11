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
}

void Backend::setSensorsList(SensorsList *sensorsList)
{
    mList = sensorsList;
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
   SensorPacketTx temp;
   QVector<Sensor> sensors = mList->items();
   temp.sensorId = sensorId;
   temp.tempSetPoint = sensors[sensorId].tempureture;
   char* dataBytes = static_cast<char*>(static_cast<void*>(&temp));
   serial->write(dataBytes);

}

void Backend::sendGeneralData()
{
  BoardPacketTx temp;
  temp.pumpSpeed = generalData.pumpSpeed;
  char* dataBytes = static_cast<char*>(static_cast<void*>(&temp));
  serial->write(dataBytes);
}

void Backend::sendPacket(char *data, int size)
{
    serial->write(data);
}

void Backend::getSensorData(QByteArray data)
{
   if(data.size() == sizeof(struct SensorPacketRx)) {
    SensorPacketRx *m = reinterpret_cast<SensorPacketRx*>(data.data());
    if(m->sendsorId < mList->items().size()) {
      mList->items()[m->sendsorId].tempureture = m->temp;
      mList->items()[m->sendsorId].current = m->current;
      mList->items()[m->sendsorId].res = m->res;
    } else {
        cout<< "getSensorData :"<< m->sendsorId << " is wrong sensorId" << endl;
    }
   } else {
       cout<< "getSensorData "<< data.size() << " must be "<<sizeof(struct SensorPacketRx);
   }
}

void Backend::getGeneralData(QByteArray data)
{
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
  } else {
      cout<< "getGeneralData "<< data.size() << " must be "<<sizeof(struct BoardPacketRx);
  }
}

void Backend::decodePacket(QByteArray data)
{
    if(data.size() > 2){
        uint32_t sum=0;
        for(int i=0; i<data.size()-1; i++) {
            sum = sum + data[i];
        }
        if( sum % 256 == static_cast<uint8_t>(data[data.size()-1])) {
          uint8_t packetCode = data[0];
          data.remove(0,1);
          if(packetCode == SensorDataPacketCode) {
              getSensorData(data);
          } else if (packetCode == PumpSpeedPacketCode) {
             getGeneralData(data);
          }
        } else {
            cout << unsigned(data[data.size()-1]) << " checsum is wrong " << sum % 256;
        }
    }
}

void Backend::createTable()
{
    if( db.openConnection() ) {
        SensorSchema sensorSchema;
        if(db.createTable(sensorSchema)) {
            cout<< "table created successfully" << endl;
            if(db.insert(sensorSchema.getSqlInsertCommand())) {
                cout<< "sensor inserted successfully" << endl;
                sensorSchema.tempureture = 10.5;
                if(db.update(sensorSchema.getSqlUpdateCommand(1))) {
                    cout<< "sensor updated successfully" << endl;
                   Sensor temp = db.findById(sensorSchema.getSqlFindById(1));
                   cout<< "sensor finded successfu successfully :" << temp.recoveryTemp << endl;
                }
            }
        }
    }
}

void Backend::updateChart(QAbstractSeries *chartSeries, int sensorId)
{
    if (chartSeries) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(chartSeries);
        QVector<Sensor> sensors = mList->items();
        if(chartSeries->name() == "Temp") {
          QVector<QPointF> points = sensors[sensorId-1].tempData;
          xySeries->replace(points);
        } else {
            QVector<QPointF> points = sensors[sensorId-1].resData;
            xySeries->replace(points);
        }
    }
}

void Backend::recieveSerialPort()
{
    QByteArray data;
    data = serial->readAll();
    for(int i=0; i< data.size(); i++) {
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
            if(packetCode == SensorDataPacketCode) {
                packetSize =  sizeof(struct SensorPacketRx);
            } else if(packetCode == PumpSpeedPacketCode) {
                packetSize =  sizeof(struct BoardPacketRx);
            }
            recieveState = recieveState + 1;
        } else {
          if( packetSize + 3 !=  recieveState) {
              dataBuf.append(data[i]);
              recieveState = recieveState + 1;
          } else {
             recieveState = 0;
          }
        }
    }
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
    }
   } else {
       serial->close();
//       connectState = false;qDebug() << "Disconndected : ";
   }

//   emit notifyInfoDataChanged();
}
