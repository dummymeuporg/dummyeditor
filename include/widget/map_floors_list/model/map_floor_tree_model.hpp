#pragma once

#include <memory>

#include <QStandardItemModel>
#include <QVariant>

namespace Editor {
class Map;
} // namespace Editor

namespace Widget {
namespace MapFloorsList {
namespace Model {
class MapTreeItem;
class MapFloorTreeModel : public QStandardItemModel {
public:
    MapFloorTreeModel(std::shared_ptr<Editor::Map>);
    MapTreeItem* mapTreeItemFromIndex(const QModelIndex&) const;
private:
    std::shared_ptr<Editor::Map> m_editorMap;
};
} // namespace Model
} // namespace MapFloorsList
} // namespace Widget
