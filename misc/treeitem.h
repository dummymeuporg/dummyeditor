#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <memory>

class QString;

namespace Misc {
    class TreeItem
    {
    public:
        explicit TreeItem(const QString& data,
                          TreeItem* parentItem = nullptr);
        ~TreeItem();

        void appendChild(TreeItem* child);

        TreeItem* child(int row);
        int childCount() const;
        int columnCount() const;
        QVariant data() const;
        int row() const;
        TreeItem* parentItem();

    private:
        QList<TreeItem*> m_childItems;
        QString m_itemData;
        TreeItem* m_parentItem;
    };
}

#endif // TREEITEM_H
