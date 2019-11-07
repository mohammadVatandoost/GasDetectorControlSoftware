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

char* Backend::makeSensorData(uint8_t sensorId)
{
   SensorPacketTx temp;
   QVector<Sensor> sensors = mList->items();
   temp.sensorId = sensorId;
   temp.tempSetPoint = sensors[sensorId].tempureture;
   char* dataBytes = static_cast<char*>(static_cast<void*>(&temp));
   return dataBytes;

}

char* Backend::makeGeneralData()
{
  BoardPacketTx temp;
  temp.pumpSpeed = generalData.pumpSpeed;
}

void Backend::sendPacket(char *data, int size)
{
    serial->write(data);
}

void Backend::getSensorData(QByteArray data)
{

}

void Backend::getGeneralData(QByteArray data)
{

}

void Backend::createTable()
{
    if( db.openConnection() ) {
        SensorSchema sensorSchema;
        if(db.createTable(sensorSchema)) {
            cout<< "table created successfully" << endl;
            if(db.insert(sensorSchema.getSqlInsertCommand())) {
                cout<< "sensor inserted successfully" << endl;
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

   emit notifyInfoDataChanged();
}
