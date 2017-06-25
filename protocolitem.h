
#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

//! [0]
class ProtocolItem
{
public:
    explicit ProtocolItem(const QList<QVariant> &data, ProtocolItem *parent = 0);
    ~ProtocolItem();

    void appendChild(ProtocolItem *child);

    ProtocolItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    ProtocolItem *parent();

private:
    QList<ProtocolItem*> childItems;
    QList<QVariant> itemData;
    ProtocolItem *parentItem;
};
//! [0]

#endif // TREEITEM_H
