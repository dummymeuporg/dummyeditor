#include <QDebug>
#include <QDomNode>

#include "treemodel.h"
#include "treeitem.h"


Misc::TreeModel::TreeModel(const QDomNode& mapsNode, QObject* parent)
    : QAbstractItemModel(parent)
{
    QString rootData("Maps");
    rootItem = new TreeItem(rootData);
    setupModelData(mapsNode, rootItem);
}

Misc::TreeModel::~TreeModel() {
    delete rootItem;
}

QModelIndex Misc::TreeModel::index(int row, int column,
                                   const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    TreeItem* parentItem;

    if (!parent.isValid()) {
        parentItem = rootItem;
    } else {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem* childItem = parentItem->child(row);

    if (nullptr != childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

QModelIndex Misc::TreeModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) {
        return QModelIndex();
    }

    TreeItem* childItem =
        static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parentItem();

    if (parentItem == rootItem) {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int Misc::TreeModel::rowCount(const QModelIndex& parent) const {
    Misc::TreeItem* parentItem = nullptr;

    if (parent.column() > 0) {
        return 0;
    }

    if (!parent.isValid()) {
        parentItem = rootItem;
    } else {
        parentItem = static_cast<Misc::TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int Misc::TreeModel::columnCount(const QModelIndex& parent) const {
    // We only have one column: the map name.
    return 1;
}

QVariant Misc::TreeModel::data(const QModelIndex& index, int role) const {

    if (index.column() > 0) {
        return QVariant();
    }

    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    return item->data();
}

Qt::ItemFlags Misc::TreeModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

QVariant Misc::TreeModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    Q_UNUSED(section);
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return rootItem->data();
    } else {
        return QVariant();
    }
}

void Misc::TreeModel::setupModelData(const QDomNode& node,
                                     TreeItem* parent)
{
    for(QDomNode n = node.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        if (n.nodeName() == "map") {
            Misc::TreeItem* item = new Misc::TreeItem(
                n.attributes().namedItem("name").nodeValue(),
                parent
            );
            parent->appendChild((item));
            setupModelData(n, item);
        }
    }
}
