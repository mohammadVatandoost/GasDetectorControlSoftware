#ifndef BROOKS0254_H
#define BROOKS0254_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "serialport.h"
#include "brookschannelmodel.h"

#define Read_SpRate 0
#define Read_VOR 1
#define Write_VOR 2
#define Write_SpRate 3

#define Free_State 10

using namespace std;

class Brooks0254 : public SerialPort
{
    Q_OBJECT
public:
    explicit Brooks0254();
    int counterRead = 1;
    QTimer *timer;
    void getSPRateData();
    static void getSPRateDataThread(QSerialPort *serialTemp);
    int readState = Free_State;
    BrooksChannelModel *brChannelModel;
    int offset = 0;
    QString recievedData;
    void decodeReadSpRate(QString temp);
    void sendReadSpRateCommand();
signals:

public slots:
    void recieveSerialPort();
    void timerSlot();

};

#endif // BROOKS0254_H
