#include "editor/blocking_layer.hpp"

#include "widget/map_levels_list/model/map_blocking_layer_tree_item.hpp"

namespace Widget {
namespace MapLevelsList {
namespace Model {

MapBlockingLayerTreeItem::MapBlockingLayerTreeItem(
    Editor::BlockingLayer& blockingLayer
) : m_blockingLayer(blockingLayer)
{
    if (m_blockingLayer.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

Editor::Layer& MapBlockingLayerTreeItem::layer() {
    return m_blockingLayer;
}

QVariant MapBlockingLayerTreeItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return QStringLiteral("Blocking layer");
    }
    return QStandardItem::data(role);
}

} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
