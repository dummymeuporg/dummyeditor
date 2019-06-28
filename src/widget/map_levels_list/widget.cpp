#include <QDebug>
#include "misc/abstractmapleveltreeitem.hpp"
#include "misc/mapleveltreemodel.hpp"

#include "widget/map_levels_list/widget.hpp"
#include "widget/map_levels_list/ui_widget.hpp"

Widget::Widget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::Widget),
      m_editorMap(nullptr),
      m_mapLevelTreeModel(nullptr)
{
    ui->setupUi(this);
}

void MapLevelsList::setEditorMap(std::shared_ptr<Editor::Map> editorMap) {
    m_editorMap = editorMap;
    reset();
    m_mapLevelTreeModel = new Misc::MapLevelTreeModel(m_editorMap);
    ui->treeViewLevels->setModel(m_mapLevelTreeModel);
}

void MapLevelsList::reset() {
    if (m_mapLevelTreeModel != nullptr) {
        delete m_mapLevelTreeModel;
        m_mapLevelTreeModel = nullptr;
    }
    ui->treeViewLevels->reset();
}

void MapLevelsList::toggleLayerVisibleState(QModelIndex selectedIndex) {
    qDebug() << "selectedIndex: " << selectedIndex;
   m_mapLevelTreeModel->mapTreeItemFromIndex(selectedIndex)->toggle();

}
