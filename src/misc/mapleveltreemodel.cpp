#include <algorithm>
#include "editormap.hpp"
#include "misc/mapleveltreeitem.hpp"
#include "misc/mapleveltreemodel.hpp"

namespace Misc {
MapLevelTreeModel::MapLevelTreeModel(std::shared_ptr<EditorMap> editorMap)
    : m_editorMap(editorMap)
{

    for (int i = m_editorMap->levelsCount() - 1; i >= 0; --i) {
        QList<QStandardItem*> levelItem {
            new QStandardItem("Level")
        };
        appendRow(levelItem);
    }
}

} // namespace Misc
