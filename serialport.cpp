#include "serialport.h"

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    serial->close();
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

bool SerialPort::connectSerialPort()
{
    if(QSerialPortInfo::availablePorts().size()>0) {
     if(!serial->isOpen()) {
         Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
              serial->setPortName(port.portName());
              cout<< " portName : " << port.portName().toStdString()<<endl;
              if(serial->open(QIODevice::ReadWrite)) {
                     cout << " conndected : "<<endl;
                     connect(serial, SIGNAL(readyRead()), this, SLOT(recieveSerialPort()));
                     return true;
                   break;
               } else {
                     cout<< "Not conndected : ";
                     serial->close();
               }
         }
         cout<< "serial can not connect"<<endl;
         return false;
     } else {
         cout<< "serial port connected before, please disconnect then connet"<< endl;
         return false;
     }
    } else {
        cout<< "there is no serial port info"<< endl;
        serial->close();
        return false;
    }
}

bool SerialPort::connectSerialPort(QString comePort)
{
    if(QSerialPortInfo::availablePorts().size()>0) {
     if(!serial->isOpen()) {
              serial->setPortName(comePort);
              if(serial->open(QIODevice::ReadWrite)) {
                     cout << " conndected : "<<endl;
                     connect(serial, SIGNAL(readyRead()), this, SLOT(recieveSerialPort()));
                     return true;
               }
         cout<< "serial can not connect to "<< comePort.toStdString() <<endl;
         return false;
     } else {
         cout<< "serial port connected before, please disconnect then connect"<< endl;
         return false;
     }
    } else {
        cout<< "there is no serial port info"<< endl;
        serial->close();
        return false;
    }
}
