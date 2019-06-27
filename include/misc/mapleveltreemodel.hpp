#pragma once

#include <memory>

#include <QStandardItemModel>
#include <QVariant>

class EditorMap;

namespace Misc {
class AbstractMapLevelTreeItem;
class MapLevelTreeModel : public QStandardItemModel {
public:
    MapLevelTreeModel(std::shared_ptr<EditorMap>);
    AbstractMapLevelTreeItem* mapTreeItemFromIndex(const QModelIndex&) const;
private:
    std::shared_ptr<EditorMap> m_editorMap;
};
} // namespace Misc
