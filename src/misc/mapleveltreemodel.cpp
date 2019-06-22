#include "misc/mapleveltreemodel.hpp"

namespace Misc {
MapLevelTreeModel::MapLevelTreeModel(std::shared_ptr<EditorMap> editorMap)
    : m_editorMap(editorMap)
{
    // XXX: setup hierarchy.
}

} // namespace Misc
