#pragma once

#include "abstractmapleveltreeitem.hpp"

class EditorLayer;
class EditorMap;

namespace Misc {
class MapLayerTreeItem : public AbstractMapLevelTreeItem {
public:
    MapLayerTreeItem(std::int8_t, EditorLayer&);
    QVariant data(int role = Qt::UserRole + 1) const override;
    virtual void toggle() override;
private:
    EditorLayer& m_editorLayer;
    std::int8_t m_position;
};
} // namespace Misc
