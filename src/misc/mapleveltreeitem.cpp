#include "misc/mapleveltreeitem.hpp"

namespace Misc {
MapLevelTreeItem::MapLevelTreeItem(const QString& content, bool checked)
    : m_content(content), m_checked(checked)
{}

void MapLevelTreeItem::setChecked(bool checked) {
    m_checked = checked;
}
} // namespace Misc
