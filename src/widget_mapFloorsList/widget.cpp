#include "widget_mapFloorsList/widget.hpp"
#include "widget_mapFloorsList/ui_widget.h"

#include "widget_mapFloorsList/map_floor_tree_item.hpp"
#include "widget_mapFloorsList/map_floor_tree_model.hpp"
#include <QDebug>

namespace MapFloorsList {

FloorListWidget::FloorListWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::MapFloorsList)
{
    m_ui->setupUi(this);
}

const MapFloorTreeModel* FloorListWidget::mapFloorTreeModel() const
{
    return m_floorTreeModel;
}

void FloorListWidget::setEditorMap(std::shared_ptr<Editor::Map> editorMap)
{
    reset();

    m_floorTreeModel = new MapFloorTreeModel(editorMap);
    m_ui->treeViewFloors->setModel(m_floorTreeModel);
}

void FloorListWidget::reset()
{
    if (m_floorTreeModel != nullptr) {
        delete m_floorTreeModel;
        m_floorTreeModel = nullptr;
    }
    m_ui->treeViewFloors->reset();
}

void FloorListWidget::toggleLayerVisibleState(QModelIndex selectedIndex)
{
    qDebug() << "Toggle Layer visibility: selectedIndex: " << selectedIndex;
    m_floorTreeModel->floorItemFromIdx(selectedIndex)->toggle();
}

void FloorListWidget::selectLayer(QModelIndex selectedIndex)
{
    auto* toSelect = m_floorTreeModel->floorItemFromIdx(selectedIndex);
    toSelect->setSelected(); // This line will trigger a signal:
}

} // namespace MapFloorsList
