#include "widget_mapFloorsList/map_floor_tree_item.hpp"

#include <QDebug>

#include "editor/floor.hpp"
#include "editor/layerBlocking.hpp"
#include "editor/layerGraphic.hpp"
#include "widget_mapFloorsList/map_layer_tree_item.hpp"

namespace MapFloorsList {

FloorTreeItem::FloorTreeItem(Editor::Floor& floor, std::size_t index)
    : m_editorFloor(floor)
    , m_index(index)
{
    updateVisibilityDisplay();

    // Put blocking layer at the top.
    appendRow(new LayerTreeItem(floor.blockingLayer(), BlockingLayer));

    auto& layersMap = floor.graphicLayers();
    for (auto& layer : layersMap) {
        appendRow(
            new LayerTreeItem(*(layer.second), GraphicLayer, layer.first));
    }
}

QVariant FloorTreeItem::data(int role) const
{
    if (role == Qt::DisplayRole) {
        return QObject::tr("Floor %1").arg(m_index);
    }
    return QStandardItem::data(role);
}

void FloorTreeItem::toggle()
{
    setVisible(! m_editorFloor.visible());
}

void FloorTreeItem::setVisible(bool visible)
{
    m_editorFloor.setVisible(visible);
    updateVisibilityDisplay();

    int nbRows = rowCount();
    for (int i = 0; i < nbRows; ++i) {
        auto* layerItem = reinterpret_cast<LayerTreeItem*>(child(i));
        layerItem->setVisible(visible);
    }
}

void FloorTreeItem::setSelected()
{
    // Nothing to do.
    qDebug() << "Selected floor.";
}

void FloorTreeItem::updateVisibilityDisplay()
{
    setEnabled(m_editorFloor.visible());
    if (m_editorFloor.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

} // namespace MapFloorsList
