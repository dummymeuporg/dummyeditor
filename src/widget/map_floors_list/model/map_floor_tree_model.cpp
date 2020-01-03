#include "widget/map_floors_list/model/map_floor_tree_model.hpp"

#include "editor/map.hpp"
#include "widget/map_floors_list/model/map_floor_tree_item.hpp"

namespace Widget {
namespace MapFloorsList {
namespace Model {

MapFloorTreeModel::MapFloorTreeModel(std::shared_ptr<Editor::Map> editorMap)
    : m_editorMap(editorMap)
{

    for (int i = m_editorMap->floorsCount() - 1; i >= 0; --i) {
        QList<QStandardItem*> floorItem {
            new MapFloorTreeItem(m_editorMap->floorAt(i), i)
        };
        appendRow(floorItem);
    }
}

MapTreeItem*
MapFloorTreeModel::mapTreeItemFromIndex(const QModelIndex& index) const
{
    return reinterpret_cast<MapTreeItem*>(itemFromIndex(index));
}

} // namespace Model
} // namespace MapFloorsList
} // namespace Widget
