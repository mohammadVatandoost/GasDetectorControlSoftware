#include "brooksthread.h"

BrooksThread::BrooksThread()
{
    //    brooksChannel = new Brooks0254();
    serial = new QSerialPort(this);
    serial->close();
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

void BrooksThread::decodeReadSpRate(QString temp)
{
//    cout<< counterRead<< " decodeReadSpRate: "<< temp.toStdString()<<endl;
    if(temp.contains(",")) {
//              cout<< temp.toStdString()<<endl;
       QStringList dataList =  temp.split(",");
       if(dataList.size()>6) {
           QString spRateReaded = dataList[5].replace(" ","");
//          cout<<counterRead<< " : "<<spRateReaded.toFloat()<< ","<< (counterRead/2)+offset <<endl;
          brChannelModel->setData(brChannelModel->index((counterRead/2)+offset, 0), spRateReaded.toFloat(), BrooksChannelModel::rateReaded);
//              counterRead = counterRead + 2;
//              getSPRateData();
       }
    }
}

void BrooksThread::sendReadSpRateCommand()
{
    QString command = "AZ.0"+QString::number(counterRead)+"K";
//    cout<< "sendReadSpRateCommand():"<<command.toStdString()<<endl;
    QByteArray temp2;
    temp2.append(command);
    serial->write(temp2);
    serial->waitForBytesWritten(100);
    QByteArray temp;
    temp.append(0X0D);
    serial->write(temp);
    serial->waitForBytesWritten(100);
}

bool BrooksThread::connectSerialPort(QString comePort)
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

void BrooksThread::goWrittingVORState(int channel, int value)
{
    this->channel = channel; VORValue = value;
    readState = Write_VOR;
}

void BrooksThread::sendVORCommand()
{
    QString command = "AZ."+QString::number((channel*2)+2)+"P29="+QString::number(VORValue);
    QByteArray temp2;
    temp2.append(command);
    cout<<"************************************"<<endl;
    cout<< counterRead<<" sendVORCommand:"<<command.toStdString()<<endl;
    serial->write(temp2);
    serial->waitForBytesWritten(200);
    QByteArray temp;
    temp.append(0X0D);
    serial->write(temp);
    serial->waitForBytesWritten(200);
}

void BrooksThread::sendSPRateCommand()
{
    QString command = "AZ."+QString::number((channel*2)+2)+"P01="+QString::number(SPRateValue, 'f', 2);
    QByteArray temp2;
    temp2.append(command);
    serial->write(temp2);
    serial->waitForBytesWritten(200);
    QByteArray temp;
    temp.append(0X0D);
    serial->write(temp);
    serial->waitForBytesWritten(200);
}

void BrooksThread::sendReadVORCommand()
{
    QString command = "AZ."+QString::number(counterRead)+"P29?";
    cout<<"sendReadVORCommand : "<< command.toStdString() << endl;
    QByteArray temp2;
    temp2.append(command);
    serial->write("AZ.2P29?");
//    serial->write(temp2);
    serial->waitForBytesWritten(100);
    QByteArray temp;
    temp.append(0X0D);
    serial->write(temp);
    serial->waitForBytesWritten(100);
}

void BrooksThread::decodeReadVOR(QString temp)
{
     cout<<counterRead<<" decodeReadVOR: "<< temp.toStdString()<<endl;
    if(temp.contains(",")) {
       QStringList dataList =  temp.split(",");
       if(dataList.size()>5) {
           QString VORReaded = dataList[4].replace(" ","");
//          cout<<counterRead<< " : "<<VORReaded.toInt()<< ","<< (counterRead/2)-1+offset <<endl;
          brChannelModel->setData(brChannelModel->index((counterRead/2)-1+offset, 0), VORReaded.toFloat(), BrooksChannelModel::VOR);
//              counterRead = counterRead + 2;
//              getSPRateData();
       }
    }
}

void BrooksThread::goWrittingSPRate(int channel, float value)
{
    this->channel = channel; SPRateValue = value;
    readState = Write_SpRate;
}

void BrooksThread::run()
{
    channel = 0+offset; VORValue = 1;
    sendVORCommand();
    QThread::msleep(500);
    channel = 1+offset; VORValue = 1;
    sendVORCommand();
    QThread::msleep(500);
    channel = 2+offset; VORValue = 1;
    sendVORCommand();
    QThread::msleep(500);
    channel = 3+offset; VORValue = 1;
    sendVORCommand();
    QThread::msleep(500);
    while(true) {
        if(serial->isOpen()) {
            cout<< "readState :"<<readState<<endl;
            if(readState == Free_State) {
                readState = Read_SpRate;
                QByteArray tempByte = serial->readAll();
                QString tempTest;tempTest.append(tempByte);
//                decodeReadVOR(tempTest);
                decodeReadSpRate(tempTest);
                recievedData.clear();
                counterRead = 1 ;
                sendReadSpRateCommand();
            } else if( readState == Read_SpRate ) {
                QByteArray tempByte = serial->readAll();
                QString tempTest;tempTest.append(tempByte);
                if(counterRead%2 == 1) {
                    decodeReadSpRate(tempTest);
                } else {
                    decodeReadVOR(tempTest);
                }
                recievedData.clear();
                counterRead = counterRead + 2;
                if( counterRead == 7) {
//                    sendReadVORCommand();
                    sendReadSpRateCommand();
                   readState = Free_State;
                } else {
                    if(counterRead%2 == 1) {
                       sendReadSpRateCommand();
                    } else {
                        sendReadVORCommand();
                    }
                }
            } else if( readState == Write_VOR ) {
                sendVORCommand();
                readState = Free_State;
            } else if( readState == Write_SpRate ) {
                sendSPRateCommand();
                readState = Free_State;
            }
        }
        QThread::msleep(500);
    }
}
