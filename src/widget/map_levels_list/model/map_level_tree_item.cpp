#include <QIcon>

#include "editor/level.hpp"

#include "widget/map_levels_list/model/map_layer_tree_item.hpp"
#include "widget/map_levels_list/model/map_level_tree_item.hpp"

namespace Widget {
namespace MapLevelsList {
namespace Model {
MapLevelTreeItem::MapLevelTreeItem(Editor::Level& level)
    : m_editorLevel(level)
{
    if (m_editorLevel.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
    for(auto it = level.graphicLayers().rbegin();
        it != level.graphicLayers().rend(); ++it)
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
} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
