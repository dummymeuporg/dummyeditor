#include "mapFloorTreeModel.hpp"

#include "editor/layerBlocking.hpp"
#include "editor/layerGraphic.hpp"
#include "editor/map.hpp"

namespace MapFloorsList {

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeModel class
// This class is the model (data) of the list of all floors of a map
//////////////////////////////////////////////////////////////////////////////

MapFloorTreeModel::MapFloorTreeModel(std::shared_ptr<Editor::Map> editorMap)
{
    for (int i = editorMap->floorsCount() - 1; i >= 0; --i) {
        size_t uiIdx    = static_cast<size_t>(i);
        auto* floorItem = new FloorTreeItem(editorMap->floorAt(uiIdx), uiIdx);
        appendRow(floorItem);
    }
}

MapTreeItem* MapFloorTreeModel::floorItemFromIdx(const QModelIndex& index) const
{
    return dynamic_cast<MapTreeItem*>(itemFromIndex(index));
}

void MapTreeItem::setVisibilityIcon(bool isVisible)
{
    setEnabled(isVisible);
    if (isVisible) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeItem class
// This class is the model (data) of a floor (containing several layers)
//////////////////////////////////////////////////////////////////////////////

FloorTreeItem::FloorTreeItem(Editor::Floor& floor, std::size_t index)
    : m_editorFloor(floor)
    , m_index(index)
{
    setVisibilityIcon(true);

    // Put blocking layer at the top.
    appendRow(new LayerTreeItem(floor.blockingLayer(), eLayerType::Blocking));

    // Then put other layers
    for (auto& layer : floor.graphicLayers()) {
        appendRow(new LayerTreeItem(*(layer.second), eLayerType::Graphic, layer.first));
    }
}

QVariant FloorTreeItem::data(int role) const
{
    if (role == Qt::DisplayRole)
        return QObject::tr("Floor %1").arg(m_index);
    return QStandardItem::data(role);
}

void FloorTreeItem::toggle()
{
    setVisible(! m_editorFloor.visible());
}

void FloorTreeItem::setVisible(bool visible)
{
    // set editor floor visibility
    m_editorFloor.setVisible(visible);

    // update visibility icon
    setVisibilityIcon(visible);

    // propagate to children
    int nbRows = rowCount();
    for (int i = 0; i < nbRows; ++i) {
        auto* layerItem = reinterpret_cast<LayerTreeItem*>(child(i));
        layerItem->setVisible(visible);
    }
}

void FloorTreeItem::setSelected()
{
    // Nothing to do.
}

//////////////////////////////////////////////////////////////////////////////
//  MapLayerTreeItem class.
// This class is the model (data) of a layer
//////////////////////////////////////////////////////////////////////////////

LayerTreeItem::LayerTreeItem(Editor::Layer& layer, eLayerType type, int8_t idx)
    : m_layer(layer)
    , m_type(type)
    , m_index(idx)
{
    setVisibilityIcon(true);
}

QVariant LayerTreeItem::data(int role) const
{
    if (role != Qt::DisplayRole) {
        return QStandardItem::data(role);
    }

    if (m_type == eLayerType::Graphic) {
        return QObject::tr("Layer %1").arg(m_index);
    } else if (m_type == eLayerType::Blocking) {
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
    setVisibilityIcon(visible);
}

void LayerTreeItem::setSelected()
{
    emit m_layer.setSelected();
}

} // namespace MapFloorsList
