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

namespace MapFloorsList {
class MapTreeItem;

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeModel class
// This class is the model (data) of the list of all floors of a map
//////////////////////////////////////////////////////////////////////////////

class MapFloorTreeModel : public QStandardItemModel
{
public:
    explicit MapFloorTreeModel(std::shared_ptr<Editor::Map>);
    MapTreeItem* floorItemFromIdx(const QModelIndex&) const;
};

} // namespace MapFloorsList

#endif // MAPFLOORTREEMODEL_H
