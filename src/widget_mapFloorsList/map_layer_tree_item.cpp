#include "widget_mapFloorsList/map_layer_tree_item.hpp"

#include "editor/layer.hpp"

namespace MapFloorsList {

LayerTreeItem::LayerTreeItem(Editor::Layer& layer, tLayerType type, int8_t idx)
    : m_layer(layer)
    , m_type(type)
    , m_index(idx)
{
    updateVisibilityDisplay();
}

QVariant LayerTreeItem::data(int role) const
{
    if (role != Qt::DisplayRole) {
        return QStandardItem::data(role);
    }

    if (m_type == GraphicLayer) {
        return QObject::tr("Layer %1").arg(m_index);
    } else if (m_type == BlockingLayer) {
        return QObject::tr("Blocking layer");
    }

    return QObject::tr("Unknown layer");
}


void LayerTreeItem::toggle()
{
    setVisible(! m_layer.visible());
}

void LayerTreeItem::setVisible(bool visible)
{
    m_layer.setVisible(visible);
    updateVisibilityDisplay();
}

void LayerTreeItem::setSelected()
{
    emit m_layer.setSelected();
}

void LayerTreeItem::updateVisibilityDisplay()
{
    setEnabled(m_layer.visible());
    if (m_layer.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

} // namespace MapFloorsList
