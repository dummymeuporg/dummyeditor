#include "widget_mapFloorsList/map_floor_tree_model.hpp"

#include "editor/map.hpp"
#include "widget_mapFloorsList/map_floor_tree_item.hpp"

namespace MapFloorsList {

MapFloorTreeModel::MapFloorTreeModel(std::shared_ptr<Editor::Map> editorMap)
{
    for (int i = editorMap->floorsCount() - 1; i >= 0; --i) {
        size_t uiIdx    = static_cast<size_t>(i);
        auto* floorItem = new FloorTreeItem(editorMap->floorAt(uiIdx), uiIdx);
        appendRow(floorItem);
    }
}

MapTreeItem* MapFloorTreeModel::floorItemFromIdx(const QModelIndex& index) const
{
    return reinterpret_cast<MapTreeItem*>(itemFromIndex(index));
}

} // namespace MapFloorsList
