#include "brooks0254.h"

Brooks0254::Brooks0254()
{
    // timer for connection check
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(1000);
}

void Brooks0254::recieveSerialPort()
{
    QByteArray data;
    QThread::msleep(100);
    data = serial->readAll();
    QString temp; temp.append(data);
    cout<< "recieveSerialPort:"<<endl;
    cout<< temp.toStdString();

}

void Brooks0254::timerSlot()
{
    if(!serial->isOpen()) {
        connectSerialPort();
    }
}
