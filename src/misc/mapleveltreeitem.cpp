#include "misc/mapleveltreeitem.hpp"

namespace Misc {
MapLevelTreeItem::MapLevelTreeItem(EditorLevel& level)
    : m_editorLevel(level)
{}

QVariant MapLevelTreeItem::data(int role) const {
    return QString("Level");
}

} // namespace Misc
