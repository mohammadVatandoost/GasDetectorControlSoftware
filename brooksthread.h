#ifndef BROOKSTHREAD_H
#define BROOKSTHREAD_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "brooks0254.h"
#include "brookschannelmodel.h"



class BrooksThread : public QThread
{
    Q_OBJECT
public:
    explicit BrooksThread();
    int counterRead = 1;
    int counterReadForEvenChannel = 1;
    void getSPRateData();
    static void getSPRateDataThread(QSerialPort *serialTemp);
    int readState = Free_State;
    BrooksChannelModel *brChannelModel;
    int offset = 0;
    QString recievedData;
    void decodeReadSpRate(QString temp);
    void sendReadSpRateCommand();
    QSerialPort *serial;
    bool connectSerialPort(QString comePort);
    void goWrittingVORState(int channel, int value);
    void sendVORCommand();
    void sendSPRateCommand();
    void sendReadVORCommand();
    void decodeReadVOR(QString temp);
    void goWrittingSPRate(int channel, float value);
    int channel, VORValue, SPRateValue;
//    Brooks0254 *brooksChannel;
signals:

public slots:

protected:
   virtual void run();
};

#endif // BROOKSTHREAD_H
