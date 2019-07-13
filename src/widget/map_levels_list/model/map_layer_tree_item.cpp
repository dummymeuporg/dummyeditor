#include "editor/layer.hpp"

#include "widget/map_levels_list/model/map_layer_tree_item.hpp"

namespace Widget {
namespace MapLevelsList {
namespace Model {



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

} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
