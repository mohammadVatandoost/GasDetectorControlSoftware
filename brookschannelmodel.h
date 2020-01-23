#ifndef BROOKSCHANNELMODEL_H
#define BROOKSCHANNELMODEL_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QAbstractListModel>

class ChannelsList;

class BrooksChannelModel : public QAbstractListModel
{
public:
    explicit BrooksChannelModel(QObject *parent = nullptr);
    Q_PROPERTY(ChannelsList *list READ list WRITE setList )

    enum {
        spRate, VOR, name, rateReaded
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // for sensorList Q_PROPERTY
    ChannelsList *list() const;
    void setList(ChannelsList *list);
private:
    ChannelsList *mList;
};

#endif // BROOKSCHANNELMODEL_H
