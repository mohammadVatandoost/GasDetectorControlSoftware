#include "brooks0254.h"

Brooks0254::Brooks0254()
{
    // timer for connection check
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(300);
}

void Brooks0254::getSPRateData()
{
    if(counterRead ==9) {
        readState = Free_State;
    } else {
      QString command = "AZ.0"+QString::number(counterRead)+"K";
      cout<< "getSPRateData():"<<command.toStdString()<<endl;
      QByteArray temp2;
      temp2.append(command);
      serial->write(temp2);
      QByteArray temp;
      temp.append(0X0D);
      serial->write(temp);
    }

}

void Brooks0254::getSPRateDataThread(QSerialPort *serialTemp)
{
    cout<< "getSPRateDataThread"<<endl;
    if(serialTemp->isOpen()) {
        cout<<"serialTemp is open"<<endl;
    }
    for(int i=0; i< 4; i++) {
        int counterTemp = (2*i)+1;
        QString command = "AZ.0"+QString::number(counterTemp)+"K";
        QByteArray temp2;
        temp2.append(command);
        serialTemp->write(temp2);
        QByteArray temp3;
        temp3.append(0X0D);
        serialTemp->write(temp3);
        cout<<counterTemp<< " : "<<command.toStdString()<<endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Brooks0254::decodeReadSpRate(QString temp)
{
    if(temp.contains(",")) {
//              cout<< temp.toStdString()<<endl;
       QStringList dataList =  temp.split(",");
       if(dataList.size()>6) {
           QString spRateReaded = dataList[5].replace(" ","");
          cout<<counterRead<< " : "<<spRateReaded.toFloat()<< ","<< (counterRead/2)+offset <<endl;
          brChannelModel->setData(brChannelModel->index((counterRead/2)+offset, 0), spRateReaded.toFloat(), BrooksChannelModel::rateReaded);
//              counterRead = counterRead + 2;
//              getSPRateData();
       }
    }
}

void Brooks0254::sendReadSpRateCommand()
{
    QString command = "AZ.0"+QString::number(counterRead)+"K";
    cout<< "sendReadSpRateCommand():"<<command.toStdString()<<endl;
    QByteArray temp2;
    temp2.append(command);
    serial->write(temp2);
    QByteArray temp;
    temp.append(0X0D);
    serial->write(temp);
}

void Brooks0254::recieveSerialPort()
{
    QByteArray data;
    QThread::msleep(200);
    data = serial->readAll();
    recievedData.append(data);
//    QString temp; temp.append(data);
//    cout<< temp.toStdString()<<endl;
//    if(readState == Read_SpRate){
//        if(temp.contains(",")) {
////              cout<< temp.toStdString()<<endl;
//           QStringList dataList =  temp.split(",");
//           if(dataList.size()>6) {
//               QString spRateReaded = dataList[5].replace(" ","");
//              cout<<counterRead<< " : "<<spRateReaded.toFloat()<< ","<< (counterRead/2)+offset <<endl;
//              brChannelModel->setData(brChannelModel->index((counterRead/2)+offset, 0), spRateReaded.toFloat(), BrooksChannelModel::rateReaded);
////              counterRead = counterRead + 2;
////              getSPRateData();
//           }
//        }
//    }

}

void Brooks0254::timerSlot()
{
//    if(!serial->isOpen()) {
//        connectSerialPort();
//    }
    if(serial->isOpen()) {
        cout<< "readState :"<<readState<<endl;
        if(readState == Free_State) {
            readState = Read_SpRate;
            decodeReadSpRate(recievedData);
            recievedData.clear();
            counterRead = 1 ;
            sendReadSpRateCommand();
        } else if( readState == Read_SpRate ) {
            decodeReadSpRate(recievedData);
            recievedData.clear();
            counterRead = counterRead + 2;
            sendReadSpRateCommand();
            if( counterRead == 7) {
               readState = Free_State;
            }
//         counterRead = 1;
//         readState = Read_SpRate;
////         getSPRateData();
//         std::thread readThread(Brooks0254::getSPRateDataThread, serial);
//         readThread.detach();
        }
    }
}
