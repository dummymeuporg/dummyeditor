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


// This line shouldn't even exist. Still here is the reason why:
//
// On the signals/slots Qt mechanism, the connect() mechanism is based on
// textual comparison.
// Thus, the slot cannot be "void toggleLayerVisibleState(::QModelIndex);"
// since Qt Designer does not seem to like it.
// Instead, one has to set "void toggleLayerVisibleState(QModelIndex);".
// Though, "QModelIndex" would be considered here to be in the
// "Widget::MapLevelsList" namespace (if it ever exists). This is ugly.
// So the following directive will create an alias that points on the
// global namespace's QModelIndex.
//
// That's it.
using QModelIndex = ::QModelIndex;

class Widget : public ::QWidget {
    Q_OBJECT
public:
    Widget(::QWidget* parent = nullptr);
    void setEditorMap(std::shared_ptr<Editor::Map>);
public slots:
    void toggleLayerVisibleState(QModelIndex);
private:
    void reset();
    Ui::MapLevelsList* ui;
    std::shared_ptr<Editor::Map> m_editorMap;
    Model::MapLevelTreeModel* m_mapLevelTreeModel;
};

} // namespace MapLevelsList
} // namespace Widget
