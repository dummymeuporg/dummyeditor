#include <QDebug>
#include "widget/map_levels_list/model/map_level_tree_item.hpp"
#include "widget/map_levels_list/model/map_level_tree_model.hpp"

#include "widget/map_levels_list/widget.hpp"
#include "widget/map_levels_list/ui_widget.h"

namespace Widget {
namespace MapLevelsList {
Widget::Widget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::MapLevelsList),
      m_editorMap(nullptr),
      m_mapLevelTreeModel(nullptr)
{
    ui->setupUi(this);
}

void Widget::setEditorMap(std::shared_ptr<Editor::Map> editorMap) {
    m_editorMap = editorMap;
    reset();
    m_mapLevelTreeModel = new Model::MapLevelTreeModel(m_editorMap);
    ui->treeViewLevels->setModel(m_mapLevelTreeModel);
}

void Widget::reset() {
    if (m_mapLevelTreeModel != nullptr) {
        delete m_mapLevelTreeModel;
        m_mapLevelTreeModel = nullptr;
    }
    ui->treeViewLevels->reset();
}

void Widget::toggleLayerVisibleState(QModelIndex selectedIndex) {
    qDebug() << "selectedIndex: " << selectedIndex;
   m_mapLevelTreeModel->mapTreeItemFromIndex(selectedIndex)->toggle();
}

void Widget::selectLayer(QModelIndex selectedIndex) {
    auto item = m_mapLevelTreeModel->mapTreeItemFromIndex(selectedIndex);
    // This line will trigger a signal:
    item->setSelected();
}

} // namespace MapLevelsList
} // namespace Widget
