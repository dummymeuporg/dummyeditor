#ifndef MAPFLOORTREEMODEL_H
#define MAPFLOORTREEMODEL_H

#include <memory>

#include <QStandardItemModel>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Map;
} // namespace Editor

namespace Widget {
namespace MapFloorsList {
namespace Model {
class MapTreeItem;

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeModel class
//////////////////////////////////////////////////////////////////////////////

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

#endif // MAPFLOORTREEMODEL_H
