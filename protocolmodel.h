
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <vector>
#include <string>
using std::vector;
using std::string;


class ProtocolItem;

//! [0]
class ProtocolModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ProtocolModel(const QString treeName,const QString &data, QObject *parent = 0);
    explicit ProtocolModel(const QString treeName, const vector<string> & data, QObject *parent = 0);
    ~ProtocolModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void setupModelData(const QStringList &lines, ProtocolItem *parent);

    ProtocolItem *rootItem;
};
//! [0]

#endif // TREEMODEL_H
