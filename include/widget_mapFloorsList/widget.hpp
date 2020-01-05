#ifndef MAPFLOORLISTWIDGET_H
#define MAPFLOORLISTWIDGET_H

#include <memory>

#include <QWidget>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

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
// This widget display a tree-view of the list of all floors of a map
//////////////////////////////////////////////////////////////////////////////

class FloorTreeWidget : public QWidget
{
    Q_OBJECT
public:
    FloorTreeWidget(QWidget* parent = nullptr);

    const MapFloorTreeModel* mapFloorTreeModel() const;

    void setEditorMap(std::shared_ptr<Editor::Map>);

public slots:
    void selectLayer(QModelIndex);
    void toggleLayerVisibleState(QModelIndex);

private:
    void reset();

private:
    Ui::MapFloorsList* m_ui;
    MapFloorTreeModel* m_floorTreeModel;
};

} // namespace MapFloorsList

#endif // MAPFLOORLISTWIDGET_H
