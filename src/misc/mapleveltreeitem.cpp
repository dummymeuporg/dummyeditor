#include "editorlevel.hpp"

#include "misc/maplayertreeitem.hpp"
#include "misc/mapleveltreeitem.hpp"

namespace Misc {
MapLevelTreeItem::MapLevelTreeItem(EditorLevel& level)
    : m_editorLevel(level)
{
    if (m_editorLevel.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
    for(auto it = level.editorLayers().rbegin();
        it != level.editorLayers().rend(); ++it)
    {
        QList<QStandardItem*> row {
            new MapLayerTreeItem(it->first, *(it->second))
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

void MapLevelTreeItem::toggle() {
    m_editorLevel.setVisible(!m_editorLevel.visible());
    if (m_editorLevel.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

} // namespace Misc
