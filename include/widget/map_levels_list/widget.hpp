#pragma once
#include <memory>

#include <QWidget>

namespace Editor {
class Map;
} // namespace Editor

namespace Ui {
class MapLevelsList;
} // namespace Ui


namespace Widget {
namespace MapLevelsList {

namespace Model {
class MapLevelTreeModel;
} // namespace Model

class Widget : public ::QWidget {
    Q_OBJECT
public:
    Widget(::QWidget* parent = nullptr);
    void setEditorMap(std::shared_ptr<Editor::Map>);
public slots:
    void toggleLayerVisibleState(::QModelIndex);
private:
    void reset();
    Ui::MapLevelsList* ui;
    std::shared_ptr<Editor::Map> m_editorMap;
    Model::MapLevelTreeModel* m_mapLevelTreeModel;
};

} // namespace MapLevelsList
} // namespace Widget
