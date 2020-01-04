#include "widget_mapFloorsList/map_floor_tree_item.hpp"

#include <QDebug>

#include "editor/floor.hpp"
#include "widget_mapFloorsList/map_blocking_layer_tree_item.hpp"
#include "widget_mapFloorsList/map_graphic_layer_tree_item.hpp"

namespace MapFloorsList {

MapFloorTreeItem::MapFloorTreeItem(Editor::Floor& floor, std::size_t index)
    : m_editorFloor(floor)
    , m_index(index)
{
    if (m_editorFloor.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }

    // Put blocking layer at the top.
    appendRow(new MapBlockingLayerTreeItem(floor.blockingLayer()));

    for (auto it = floor.graphicLayers().rbegin();
         it != floor.graphicLayers().rend(); ++it) {
        appendRow(new MapGraphicLayerTreeItem(it->first, *(it->second)));
    }
}

QVariant MapFloorTreeItem::data(int role) const
{
    if (role == Qt::DisplayRole) {
        return QStringLiteral("Floor %1").arg(m_index);
    }
    return QStandardItem::data(role);
}

void MapFloorTreeItem::toggle()
{
    setVisible(! m_editorFloor.visible());
}

void MapFloorTreeItem::setVisible(bool visible)
{
    m_editorFloor.setVisible(visible);
    if (m_editorFloor.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }

    for (int i = 0; i < rowCount(); ++i) {
        MapLayerTreeItem* layerItem =
            reinterpret_cast<MapLayerTreeItem*>(child(i));
        layerItem->setVisible(visible);
    }
}

void MapFloorTreeItem::setSelected()
{
    // Nothing to do.
    qDebug() << "Selected floor.";
}

} // namespace MapFloorsList
