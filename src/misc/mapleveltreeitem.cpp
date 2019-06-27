#include "editorlevel.hpp"

#include "misc/mapleveltreeitem.hpp"

namespace Misc {
MapLevelTreeItem::MapLevelTreeItem(EditorLevel& level)
    : m_editorLevel(level)
{
    setIcon(QIcon(":/icons/icon_eye.png"));
    for(auto it = level.editorLayers().rbegin();
        it != level.editorLayers().rend(); ++it)
    {
        QList<QStandardItem*> row {
            new QStandardItem(
                QIcon(":/icons/icon_eye.png"),
                QStringLiteral("Layer %1").arg(it->first)
            )
        };
        appendRow(row);
    }
}

QVariant MapLevelTreeItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return QStringLiteral("Level");
    }
    return QStandardItem::data(role);
}

} // namespace Misc
