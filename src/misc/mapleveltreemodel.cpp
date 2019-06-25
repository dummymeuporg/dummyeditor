#include <algorithm>
#include "editormap.hpp"
#include "misc/mapleveltreeitem.hpp"
#include "misc/mapleveltreemodel.hpp"

namespace Misc {
MapLevelTreeModel::MapLevelTreeModel(std::shared_ptr<EditorMap> editorMap)
    : m_editorMap(editorMap)
{
    // XXX: setup hierarchy.
    QList<QStandardItem*> headers{
        new QStandardItem("Visible"),
        new QStandardItem("Element")
    };
    appendColumn(headers);
    for (int i = m_editorMap->levelsCount() - 1; i >= 0; --i) {
        QList<QStandardItem*> levelItem {
            new MapLevelTreeItem("Level", true)
        };
        const Dummy::Core::MapLevel& mapLevel(m_editorMap->mapLevels()[i]);
        for (auto it = mapLevel.layers().rbegin();
             it != mapLevel.layers().rend();
             ++it)
        {
            QList<QStandardItem*> layerItem {
                new MapLevelTreeItem(
                    QStringLiteral("Layer %1").arg(it->first),
                    true
                )
            };
            levelItem.first()->appendRow(layerItem);
        }
        appendRow(levelItem);
    }
}

QVariant MapLevelTreeModel::headerData(
    int section,
    Qt::Orientation orientation,
    int role
) const {
    return QVariant();
}

QVariant MapLevelTreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    MapLevelTreeItem *item =
        static_cast<MapLevelTreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0) {
        return static_cast<int>(
            item->checked() ? Qt::Checked : Qt::Unchecked
        );
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.column() == 1) {
        return item->content();
    }

    return item->data(index.column());
}

Qt::ItemFlags MapLevelTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}

} // namespace Misc
