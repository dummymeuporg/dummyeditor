#include "mapsTreeModel.hpp"

#include <QDomNode>

MapsTreeModel::MapsTreeModel(const QDomNode& mapsNode)
{
    XmlMapToQItem(mapsNode, invisibleRootItem());
}

void MapsTreeModel::XmlMapToQItem(const QDomNode& node, QStandardItem* parent)
{
    const auto& children = node.childNodes();
    int nbChildren       = children.count();

    for (int i = 0; i < nbChildren; ++i) {
        const auto& n = children.at(i);
        if (n.nodeName() == "map") {
            QString mapName = n.attributes().namedItem("name").nodeValue();
            QStandardItem* mapItem = new QStandardItem(mapName);
            parent->appendRow(mapItem);
            XmlMapToQItem(n, mapItem);
        }
    }
}

QVariant MapsTreeModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0)
            return QString("Maps");
    }
    return QVariant();
}
