#include <QList>
#include <QVariant>

#include "treeitem.h"

Misc::TreeItem::TreeItem(const QString& data,
                         TreeItem* parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

Misc::TreeItem::~TreeItem() {
    qDeleteAll(m_childItems);
}

void Misc::TreeItem::appendChild(TreeItem* item) {
    m_childItems.append(item);
}

Misc::TreeItem* Misc::TreeItem::child(int row) {
    return m_childItems.value(row);
}

int Misc::TreeItem::childCount() const {
    return m_childItems.count();
}

int Misc::TreeItem::row() const {
    if (m_parentItem) {
        return m_parentItem->m_childItems.indexOf(
            const_cast<TreeItem*>(this)
        );
    } else {
        return 0;
    }
}

int Misc::TreeItem::columnCount() const {
    return m_itemData.count();
}

QVariant Misc::TreeItem::data() const {
    return m_itemData;
}

Misc::TreeItem* Misc::TreeItem::parentItem() {
    return m_parentItem;
}
