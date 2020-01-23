#include "brookschannelmodel.h"

BrooksChannelModel::BrooksChannelModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}

int BrooksChannelModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    // FIXME: Implement me!
    return mList->items().size();
}

QVariant BrooksChannelModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    const BrooksChannel item = mList->items().at(index.row());
    switch (role) {
     case spRate:
        return QVariant(item.spRate);
     case VOR:
        return QVariant(item.VOR);
    case name:
       return QVariant( QString::fromStdString(item.name) );
    case rateReaded:
       return QVariant(item.rateReaded);
    }

    return QVariant();
}

bool BrooksChannelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    BrooksChannel item = mList->items().at(index.row());
    switch (role) {
     case spRate:
        item.spRate = value.toDouble();
     case VOR:
       item.VOR = value.toInt();
     case name:
       item.name = value.toString().toStdString();
     case rateReaded:
       item.rateReaded = value.toDouble();
    }

    if(mList->set(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

QHash<int, QByteArray> BrooksChannelModel::roleNames() const
{

}

Qt::ItemFlags BrooksChannelModel::flags(const QModelIndex &index) const
{

}

ChannelsList *BrooksChannelModel::list() const
{

}

void BrooksChannelModel::setList(ChannelsList *list)
{

}
