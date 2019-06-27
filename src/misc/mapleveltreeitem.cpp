#include "editorlevel.hpp"

#include "misc/mapleveltreeitem.hpp"

namespace Misc {
MapLevelTreeItem::MapLevelTreeItem(EditorLevel& level)
    : m_editorLevel(level)
{
    // XXX: add rows for layers
    for (const auto& [position, layer]: level.editorLayers()) {
        QList<QStandardItem*> row {
            new QStandardItem("Layer")
        };
        appendRow(row);
    }
}

QVariant MapLevelTreeItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return QString("Level");
    }
    return QStandardItem::data(role);
}

} // namespace Misc
