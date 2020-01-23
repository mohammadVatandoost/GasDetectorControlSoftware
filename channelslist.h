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

signals:
   void preItemAppended();
   void postItemAppended();
   void setData(const QModelIndex &index, const QVariant &value, int role);

   void preItemRemoved(int index);
   void postItemRemoved();
   void notifyInfoDataChanged();
};

#endif // CHANNELSLIST_H
