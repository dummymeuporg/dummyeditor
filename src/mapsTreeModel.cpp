#include "mapsTreeModel.hpp"

#include <QDomNode>

MapTreeModel::MapTreeModel(const QDomNode& mapsNode)
{
    setupModelData(mapsNode, invisibleRootItem());
}

void MapTreeModel::setupModelData(const QDomNode& node,
                                        QStandardItem* parent)
{
    for (QDomNode n = node.firstChild(); ! n.isNull(); n = n.nextSibling()) {
        if (n.nodeName() == "map") {
            QList<QStandardItem*> preparedRow{new QStandardItem(
                n.attributes().namedItem("name").nodeValue())};
            parent->appendRow(preparedRow);
            setupModelData(n, preparedRow.first());
        }
    }
}

QVariant MapTreeModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Maps");
            }
        }
    }
    return QVariant();
}
