#include "mapFloorTreeWidget.hpp"
#include "ui_mapFloorTreeWidget.h"

#include "mapFloorTreeModel.hpp"

namespace MapFloorsList {

FloorListWidget::FloorListWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::MapFloorsList)
{
    m_ui->setupUi(this);
}
FloorListWidget::~FloorListWidget() {}

void FloorListWidget::setEditorMap(std::shared_ptr<Editor::Map> editorMap)
{
    m_floorTreeModel.reset(new MapFloorTreeModel(editorMap));
    m_ui->treeViewFloors->setModel(m_floorTreeModel.get());
}

void FloorListWidget::reset()
{
    m_floorTreeModel.reset();
    m_ui->treeViewFloors->reset();
}

void FloorListWidget::on_treeViewFloors_doubleClicked(const QModelIndex& idx)
{
    m_floorTreeModel->floorItemFromIdx(idx)->toggle();
}

void FloorListWidget::on_treeViewFloors_clicked(const QModelIndex& idx)
{
    if (m_floorTreeModel == nullptr)
        return;

    auto* itemSelected = m_floorTreeModel->floorItemFromIdx(idx);
    if (m_floorTreeModel == nullptr)
        return;

    itemSelected->setSelected(); // This line will trigger a signal
}

} // namespace MapFloorsList
