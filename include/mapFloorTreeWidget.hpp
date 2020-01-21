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

//////////////////////////////////////////////////////////////////////////////
//  Widget class
// This widget display a tree-view of the list of all floors of a map
//////////////////////////////////////////////////////////////////////////////

class FloorListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FloorListWidget(QWidget* parent = nullptr);
    virtual ~FloorListWidget() override;

    void setEditorMap(std::shared_ptr<Editor::Map>);
    void reset();

public slots:
    void on_treeViewFloors_clicked(const QModelIndex& index);
    void on_treeViewFloors_doubleClicked(const QModelIndex& index);

private:
    std::unique_ptr<Ui::MapFloorsList> m_ui;
    std::unique_ptr<MapFloorTreeModel> m_floorTreeModel;
};

} // namespace MapFloorsList

#endif // MAPFLOORLISTWIDGET_H
