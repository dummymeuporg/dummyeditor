#pragma once
#include <memory>

#include <QWidget>

class EditorMap;

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
    void setEditorMap(std::shared_ptr<EditorMap>);
public slots:
    void toggleLayerVisibleState(QModelIndex);
private:
    void reset();
    Ui::MapLevelsList* ui;
    std::shared_ptr<EditorMap> m_editorMap;
    Misc::MapLevelTreeModel* m_mapLevelTreeModel;
};
