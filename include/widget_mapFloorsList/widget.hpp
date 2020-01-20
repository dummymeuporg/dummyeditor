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
class MapTreeItem;


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

class FloorListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FloorListWidget(QWidget* parent = nullptr);

    const MapFloorTreeModel* mapFloorTreeModel() const;

    void setEditorMap(std::shared_ptr<Editor::Map>);

public slots:
    void selectLayer(QModelIndex);
    void toggleLayerVisibleState(QModelIndex);
    void on_treeViewFloors_clicked(const QModelIndex& index);

signals:
    void treeItemSelected(const MapTreeItem&);

private:
    void reset();

    Ui::MapFloorsList* m_ui             = nullptr;
    MapFloorTreeModel* m_floorTreeModel = nullptr;
};

} // namespace MapFloorsList

#endif // MAPFLOORLISTWIDGET_H
