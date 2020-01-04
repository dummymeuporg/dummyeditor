#ifndef MAPFLOORLISTWIDGET_H
#define MAPFLOORLISTWIDGET_H

#include <memory>

#include <QWidget>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class MapGraphicsScene;
} // namespace GraphicMap

namespace Editor {
class Map;
} // namespace Editor

namespace Ui {
class MapFloorsList;
} // namespace Ui


namespace MapFloorsList {
class MapFloorTreeModel;


// This line shouldn't even exist. Still here is the reason why:
//
// On the signals/slots Qt mechanism, the connect() mechanism is based on
// textual comparison.
// Thus, the slot cannot be "void toggleLayerVisibleState(::QModelIndex);"
// since Qt Designer does not seem to like it.
// Instead, one has to set "void toggleLayerVisibleState(QModelIndex);".
// Though, "QModelIndex" would be considered here to be in the
// "MapFloorsList" namespace (if it ever exists). This is ugly.
// So the following directive will create an alias that points on the
// global namespace's QModelIndex.
//
// That's it.
using QModelIndex = ::QModelIndex;

//////////////////////////////////////////////////////////////////////////////
//  Widget class
//////////////////////////////////////////////////////////////////////////////

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    void setEditorMap(std::shared_ptr<Editor::Map>);
    const MapFloorTreeModel* mapFloorTreeModel() const
    {
        return m_mapFloorTreeModel;
    }

signals:
    void selectedLayerChanged();

public slots:
    void selectLayer(QModelIndex);
    void toggleLayerVisibleState(QModelIndex);

private:
    void reset();
    Ui::MapFloorsList* m_ui;
    std::shared_ptr<Editor::Map> m_editorMap;
    MapFloorTreeModel* m_mapFloorTreeModel;
    GraphicMap::MapGraphicsScene* m_mapScene;
};

} // namespace MapFloorsList

#endif // MAPFLOORLISTWIDGET_H
