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
//////////////////////////////////////////////////////////////////////////////

class MapFloorTreeModel : public QStandardItemModel
{
public:
    MapFloorTreeModel(std::shared_ptr<Editor::Map>);
    MapTreeItem* mapTreeItemFromIndex(const QModelIndex&) const;

private:
    std::shared_ptr<Editor::Map> m_editorMap;
};

} // namespace MapFloorsList

#endif // MAPFLOORTREEMODEL_H
