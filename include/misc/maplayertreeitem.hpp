#pragma once

#include "abstractmapleveltreeitem.hpp"

namespace Editor {
class Layer;
class Map;
} // namespace Editor

namespace Misc {
class MapLayerTreeItem : public AbstractMapLevelTreeItem {
public:
    MapLayerTreeItem(std::int8_t, Editor::Layer&);
    QVariant data(int role = Qt::UserRole + 1) const override;
    virtual void toggle() override;
private:
    Editor::Layer& m_editorLayer;
    std::int8_t m_position;
};
} // namespace Misc
