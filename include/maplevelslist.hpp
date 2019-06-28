#pragma once
#include <memory>

#include <QWidget>

namespace Editor {
class Map;
} // namespace Editor

namespace Misc {
class MapLevelTreeModel;
}

namespace Ui {
class MapLevelsList;
}

class MapLevelsList : public QWidget {
    Q_OBJECT
public:
    MapLevelsList(QWidget* parent = nullptr);
    void setEditorMap(std::shared_ptr<Editor::Map>);
public slots:
    void toggleLayerVisibleState(QModelIndex);
private:
    void reset();
    Ui::MapLevelsList* ui;
    std::shared_ptr<Editor::Map> m_editorMap;
    Misc::MapLevelTreeModel* m_mapLevelTreeModel;
};
