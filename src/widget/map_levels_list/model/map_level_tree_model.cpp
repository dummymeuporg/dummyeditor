#include <algorithm>
#include "editor/map.hpp"
#include "widget/map_levels_list/model/map_level_tree_model.hpp"
#include "widget/map_levels_list/model/map_level_tree_item.hpp"

namespace Widget {
namespace MapLevelsList {
namespace Model {
MapLevelTreeModel::MapLevelTreeModel(std::shared_ptr<Editor::Map> editorMap)
    : m_editorMap(editorMap)
{

    for (int i = m_editorMap->levelsCount() - 1; i >= 0; --i) {
        QList<QStandardItem*> levelItem {
            new MapLevelTreeItem(m_editorMap->levelAt(i))
        };
        appendRow(levelItem);
    }
}

MapTreeItem*
MapLevelTreeModel::mapTreeItemFromIndex(const QModelIndex& index) const
{
    return reinterpret_cast<MapTreeItem*>(itemFromIndex(index));
}

} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
