#ifndef SENSORMODEL_H
#define SENSORMODEL_H

//#include <QObject>
#include <QAbstractListModel>
#include "sensor.h"

class SensorsList;

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SensorsList *list READ list WRITE setList )
public:
    explicit SensorModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // for sensorList Q_PROPERTY
    SensorsList *list() const;
    void setList(SensorsList *list);
private:
    SensorsList *mList;
};

#endif // SENSORMODEL_H
