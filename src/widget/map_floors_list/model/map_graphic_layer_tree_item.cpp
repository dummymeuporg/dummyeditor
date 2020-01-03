#include "widget/map_floors_list/model/map_graphic_layer_tree_item.hpp"

#include <QDebug>

#include "editor/graphic_layer.hpp"

namespace MapFloorsList {

MapGraphicLayerTreeItem::MapGraphicLayerTreeItem(
    std::int8_t position,
    Editor::GraphicLayer& graphicLayer)
    : m_position(position)
    , m_graphicLayer(graphicLayer)
{
    if (m_graphicLayer.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

Editor::Layer& MapGraphicLayerTreeItem::layer() {
    return m_graphicLayer;
}

QVariant MapGraphicLayerTreeItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return QStringLiteral("Layer %1").arg(m_position);
    }
    return QStandardItem::data(role);
}

void MapGraphicLayerTreeItem::setSelected() {
    qDebug() << "Selected graphic layer.";
    emit m_graphicLayer.setSelected();
}

} // namespace MapFloorsList
