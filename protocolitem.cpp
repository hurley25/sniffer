
/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include <QStringList>

#include "protocolitem.h"

//! [0]
ProtocolItem::ProtocolItem(const QList<QVariant> &data, ProtocolItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
ProtocolItem::~ProtocolItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
void ProtocolItem::appendChild(ProtocolItem *item)
{
    childItems.append(item);
}
//! [2]

//! [3]
ProtocolItem *ProtocolItem::child(int row)
{
    return childItems.value(row);
}
//! [3]

//! [4]
int ProtocolItem::childCount() const
{
    return childItems.count();
}
//! [4]

//! [5]
int ProtocolItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant ProtocolItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
ProtocolItem *ProtocolItem::parent()
{
    return parentItem;
}
//! [7]

//! [8]
int ProtocolItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<ProtocolItem*>(this));

    return 0;
}
//! [8]
