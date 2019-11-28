#include "sensormodel.h"
#include "sensorslist.h"

SensorModel::SensorModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

//QVariant SensorModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

int SensorModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    // FIXME: Implement me!
    return mList->items().size();
}

QVariant SensorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    const Sensor item = mList->items().at(index.row());
    switch (role) {
     case tempureture:
        return QVariant(item.tempureture);
     case res:
        return QVariant(item.res);
    case current:
       return QVariant(item.current);
    case lowPassFilter:
       return QVariant(item.lowPassFilter);
    case R0:
       return QVariant(item.R0);
    case RThereshould:
       return QVariant(item.RThereshould);
    case operationTime:
       return QVariant(item.operationTime);
    case recoveryTime:
       return QVariant(item.recoveryTime);
    case recoveryTemp:
       return QVariant(item.recoveryTemp);
    case gasType:
       return QVariant(item.gasType);
    case pressureType:
       return QVariant(item.pressureType);
    case equation:
       return QVariant(item.equation);
    case RtoR0OrRtoDeltaR:
       return QVariant(item.RtoR0OrRtoDeltaR);
    case tempActive:
       return QVariant(item.tempActive);
    case heaterActive:
       return QVariant::fromValue(item.heaterActive);
    case sensorActive:
       return QVariant::fromValue(item.sensorActive);
    case alghoritmRunning:
       return QVariant::fromValue(item.alghoritmRunning);
    }

    return QVariant();
}

bool SensorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    Sensor item = mList->items().at(index.row());
    switch (role) {
     case tempureture:
        item.tempureture = value.toFloat();
     case res:
       item.res = value.toInt();
     case current:
       item.current = value.toUInt();
     case lowPassFilter:
       item.lowPassFilter = value.toUInt();
     case R0:
       item.R0 = value.toUInt();
     case RThereshould:
       item.RThereshould = value.toUInt();
     case operationTime:
       item.operationTime = value.toUInt();
     case recoveryTemp:
       item.recoveryTemp = value.toFloat();
     case gasType:
       item.gasType = value.toString();
//     case type:
//       item.type = value.value<ValueType>();
//     case equation:
//       item.equation = value.value<FormulType>();
     case RtoR0OrRtoDeltaR:
       item.RtoR0OrRtoDeltaR = value.toBool();
     case tempActive:
       item.tempActive = value.toBool();
     case heaterActive:
       item.heaterActive = value.toBool();
     case sensorActive:
       item.sensorActive = value.toBool();
    case alghoritmRunning:
      item.alghoritmRunning = value.toBool();
    }

    if(mList->setSensorItem(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
    return false;
}

QHash<int, QByteArray> SensorModel::roleNames() const
{
  QHash<int, QByteArray> names;
  names[tempureture] = "tempureture";
  names[res] = "res" ;
  names[current] = "current" ;
  names[lowPassFilter] = "lowPassFilter" ;
  names[R0] = "R0" ;
  names[RThereshould] = "RThereshould";
  names[operationTime] = "operationTime" ;
  names[recoveryTemp] = "recoveryTemp" ;
  names[gasType] = "gasType";
  names[pressureType] = "pressureType" ;
  names[equation] = "equation" ;
  names[RtoR0OrRtoDeltaR] = "RtoR0OrRtoDeltaR" ;
  names[tempActive] = "tempActive" ;
  names[heaterActive] = "heaterActive" ;
  names[sensorActive] = "sensorActive" ;
  names[alghoritmRunning] = "alghoritmRunning" ;
  return names;
}

Qt::ItemFlags SensorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

SensorsList *SensorModel::list() const
{
    return mList;
}

void SensorModel::setList(SensorsList *list)
{
    beginResetModel();
    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList) {
        connect(mList, &SensorsList::preItemAppended, this, [this]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &SensorsList::postItemAppended, this, [this]() {
          endInsertRows();
        });
        connect(mList, &SensorsList::preItemRemoved, this, [this](int index) {
          beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &SensorsList::postItemRemoved, this, [this]() {
          endRemoveRows();
        });
    }

    endResetModel();
}

