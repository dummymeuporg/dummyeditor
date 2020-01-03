#include "widget_mapFloorsList/map_layer_tree_item.hpp"

#include "editor/layer.hpp"

namespace MapFloorsList {

void MapLayerTreeItem::toggle() {
    setVisible(!layer().visible());
}

void MapLayerTreeItem::setVisible(bool visible) {
    layer().setVisible(visible);
    if (layer().visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

} // namespace MapFloorsList
