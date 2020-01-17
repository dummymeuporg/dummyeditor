#ifndef MAPLAYERTREEITEM_H
#define MAPLAYERTREEITEM_H

#include "widget_mapFloorsList/map_tree_item.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Layer;
} // namespace Editor

namespace MapFloorsList {
enum class eLayerType
{
    Graphic,
    Blocking
};

//////////////////////////////////////////////////////////////////////////////
//  MapLayerTreeItem class.
// This class is the model (data) of a layer
//////////////////////////////////////////////////////////////////////////////

class LayerTreeItem : public MapTreeItem
{
public:
    LayerTreeItem(Editor::Layer& layer, eLayerType type, int8_t index = 0);

    QVariant data(int role = Qt::UserRole + 1) const override;

    void toggle() override;
    void setVisible(bool isVisible) override;
    void setSelected() override;

private:
    void updateVisibilityDisplay();

    Editor::Layer& m_layer;
    eLayerType m_type;
    int8_t m_index;
};

} // namespace MapFloorsList

#endif // MAPLAYERTREEITEM_H
