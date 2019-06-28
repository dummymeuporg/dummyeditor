#include <algorithm>
#include "editor/map.hpp"
#include "misc/abstractmapleveltreeitem.hpp"
#include "misc/mapleveltreeitem.hpp"
#include "misc/mapleveltreemodel.hpp"

namespace Misc {
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

AbstractMapLevelTreeItem*
MapLevelTreeModel::mapTreeItemFromIndex(const QModelIndex& index) const
{
    return reinterpret_cast<AbstractMapLevelTreeItem*>(itemFromIndex(index));
}

} // namespace Misc
