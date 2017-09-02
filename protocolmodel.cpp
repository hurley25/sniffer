
/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include "protocolitem.h"
#include "protocolmodel.h"

#include <QStringList>

ProtocolModel::ProtocolModel(const QString treeName, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << treeName;//<<" " ;
    rootItem = new ProtocolItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

ProtocolModel::ProtocolModel(const QString treeName, const vector<string> &data, QObject *parent)
{
    QList<QVariant> rootData;
    rootData << treeName;
    rootItem = new ProtocolItem(rootData);
    QStringList str_list;
    for(const auto & str:data)
        for(const auto & line: QString(str.c_str()).split("\n"))
            str_list.push_back(line);
    setupModelData(str_list, rootItem);
}

ProtocolModel::~ProtocolModel()
{
    delete rootItem;
}


int ProtocolModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<ProtocolItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}


QVariant ProtocolModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    ProtocolItem *item = static_cast<ProtocolItem*>(index.internalPointer());

    return item->data(index.column());
}


Qt::ItemFlags ProtocolModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}


QVariant ProtocolModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


QModelIndex ProtocolModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ProtocolItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ProtocolItem*>(parent.internalPointer());

    ProtocolItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


QModelIndex ProtocolModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ProtocolItem *childItem = static_cast<ProtocolItem*>(index.internalPointer());
    ProtocolItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


int ProtocolModel::rowCount(const QModelIndex &parent) const
{
    ProtocolItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ProtocolItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void ProtocolModel::setupModelData(const QStringList &lines, ProtocolItem *parent)
{
    QList<ProtocolItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {///处理所有行
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ")///跳过前导空白
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();//去后导空格

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);///使用\t分割
            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];///全部加到columnData

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }
            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new ProtocolItem(columnData, parents.last()));
        }
        ++number;
    }
}
