#include "channelslist.h"

ChannelsList::ChannelsList()
{

}

QVector<BrooksChannel> ChannelsList::items()
{
    return channelItems;
}

void ChannelsList::addChannelItem(BrooksChannel item)
{
    channelItems.append(item);
}

bool ChannelsList::setChannelItem(int index, BrooksChannel brooksChannel)
{
    if(index <0 || index >= channelItems.size())
        return false;

    channelItems[index] = brooksChannel;
    return true;
}
