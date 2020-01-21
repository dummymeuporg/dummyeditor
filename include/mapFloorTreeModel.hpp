#ifndef MAPFLOORTREEMODEL_H
#define MAPFLOORTREEMODEL_H

#include <memory>

#include <QStandardItemModel>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Floor;
class Layer;
class Map;
} // namespace Editor

namespace MapFloorsList {
enum class eLayerType
{
    Graphic,
    Blocking
};

//////////////////////////////////////////////////////////////////////////////
//  MapTreeItem interface
//////////////////////////////////////////////////////////////////////////////

class MapTreeItem : public QStandardItem
{
public:
    virtual void toggle()         = 0;
    virtual void setVisible(bool) = 0;
    virtual void setSelected()    = 0;
};

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeModel class
// This class is the model (data) of the list of all floors of a map
//////////////////////////////////////////////////////////////////////////////

class MapFloorTreeModel : public QStandardItemModel
{
public:
    explicit MapFloorTreeModel(std::shared_ptr<Editor::Map>);
    MapTreeItem* floorItemFromIdx(const QModelIndex&) const;
};

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeItem class
// This class is the model (data) of a floor (containing several layers)
//////////////////////////////////////////////////////////////////////////////

class FloorTreeItem : public MapTreeItem
{
public:
    explicit FloorTreeItem(Editor::Floor& floor, std::size_t index);

    QVariant data(int role = Qt::UserRole + 1) const override;

    void toggle() override;
    void setVisible(bool) override;
    void setSelected() override;

private:
    Editor::Floor& m_editorFloor;
    std::size_t m_index;
};

//////////////////////////////////////////////////////////////////////////////
//  MapLayerTreeItem class.
// This class is the model (data) of a layer
//////////////////////////////////////////////////////////////////////////////

class LayerTreeItem : public MapTreeItem
{
public:
    LayerTreeItem(Editor::Layer& layer, eLayerType type, int8_t index = 0);

    QVariant data(int role = Qt::UserRole + 1) const override;

    void toggle() override;
    void setVisible(bool isVisible) override;
    void setSelected() override;

private:
    Editor::Layer& m_layer;
    eLayerType m_type;
    int8_t m_index;
};

} // namespace MapFloorsList

#endif // MAPFLOORTREEMODEL_H
