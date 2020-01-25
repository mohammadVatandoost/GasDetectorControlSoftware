#include "brookschannelmodel.h"
#include "channelslist.h"

BrooksChannelModel::BrooksChannelModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
   mList = new ChannelsList();
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

    cout<< "setData index.row():"<< index.row()<<", role:"<< role << endl;
    BrooksChannel item = mList->items().at(index.row());
    switch (role) {
     case spRate:
        cout<<"spRate role "<<value.toDouble()<<endl;
        item.spRate = value.toDouble();
        break;
     case VOR:
        cout<<"VOR role "<<value.toInt()<<endl;
       item.VOR = value.toInt();
       break;
     case name:
        cout<<"name role "<<value.toString().toStdString()<<endl;
       item.name = value.toString().toStdString();
       break;
     case rateReaded:
        cout<<"rateReaded role :"<<value.toDouble()<<endl;
       item.rateReaded = value.toDouble();
       break;
    }

    if(mList->setChannelItem(index.row(), item)) {
        cout<< "emit data changed:"<< index.row()<< ", role:"<<role<<endl;
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

QHash<int, QByteArray> BrooksChannelModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[spRate] = "spRate";
    names[VOR] = "VOR" ;
    names[name] = "name" ;
    names[rateReaded] = "rateReaded" ;
    return names;
}

Qt::ItemFlags BrooksChannelModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

ChannelsList *BrooksChannelModel::list() const
{
      return mList;
}

void BrooksChannelModel::setList(ChannelsList *list)
{
    beginResetModel();
    if(mList)
        mList->disconnect(this);

    mList = list;

    endResetModel();
}
