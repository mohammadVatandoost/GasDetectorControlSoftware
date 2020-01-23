#ifndef BROOKS0254_H
#define BROOKS0254_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "serialport.h"

class Brooks0254 : public SerialPort
{
    Q_OBJECT
public:
    explicit Brooks0254();

    QTimer *timer;
signals:

public slots:
    void recieveSerialPort();
    void timerSlot();

};

#endif // BROOKS0254_H
