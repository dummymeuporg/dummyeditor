#include "misc/mapleveltreemodel.hpp"

namespace Misc {
MapLevelTreeModel::MapLevelTreeModel(std::shared_ptr<EditorMap> editorMap)
    : m_editorMap(editorMap)
{
    // XXX: setup hierarchy.
}

QVariant MapLevelTreeModel::headerData(
    int section,
    Qt::Orientation orientation,
    int role
) const {
    return QVariant();
}

} // namespace Misc
