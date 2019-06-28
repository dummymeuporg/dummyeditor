#pragma once

#include "abstractmapleveltreeitem.hpp"

namespace Editor {
class Level;
class Map;
} // namespace Editor

namespace Misc {
class MapLevelTreeItem : public AbstractMapLevelTreeItem {
public:
    MapLevelTreeItem(Editor::Level&);
    QVariant data(int role = Qt::UserRole + 1) const override;
    virtual void toggle() override;
private:
    Editor::Level& m_editorLevel;
};
} // namespace Misc
