#ifndef CHANNELSLIST_H
#define CHANNELSLIST_H

#include <QObject>
#include <QVector>
#include "brookschannel.h"

class ChannelsList: public QObject
{
     Q_OBJECT

public:
    ChannelsList();
    QVector<BrooksChannel> channelItems;
    QVector<BrooksChannel> items();
    void addChannelItem(BrooksChannel item);
    bool setChannelItem(int index, BrooksChannel brooksChannel);
};

#endif // CHANNELSLIST_H
