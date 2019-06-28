#pragma once

#include <memory>

#include <QStandardItemModel>
#include <QVariant>

namespace Editor {
class Map;
} // namespace Editor

namespace Misc {
class AbstractMapLevelTreeItem;
class MapLevelTreeModel : public QStandardItemModel {
public:
    MapLevelTreeModel(std::shared_ptr<Editor::Map>);
    AbstractMapLevelTreeItem* mapTreeItemFromIndex(const QModelIndex&) const;
private:
    std::shared_ptr<Editor::Map> m_editorMap;
};
} // namespace Misc
