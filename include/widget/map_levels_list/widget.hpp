#pragma once
#include <memory>

#include <QWidget>

namespace Editor {
class Map;
} // namespace Editor

namespace Misc {
class MapLevelTreeModel;
}

namespace Widget {
namespace MapLevelsList {
namespace Ui {
class Widget;
} // namespace Ui

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    void setEditorMap(std::shared_ptr<Editor::Map>);
public slots:
    void toggleLayerVisibleState(QModelIndex);
private:
    void reset();
    Ui::Widget* ui;
    std::shared_ptr<Editor::Map> m_editorMap;
    Misc::MapLevelTreeModel* m_mapLevelTreeModel;
};

} // namespace MapLevelsList
} // namespace Widget
