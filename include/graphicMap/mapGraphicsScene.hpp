#ifndef MAPGRAPHICSSCENE_H
#define MAPGRAPHICSSCENE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <memory>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////
template <typename T> using vec_uniq = std::vector<std::unique_ptr<T>>;

namespace Editor {
class Floor;
using Floors = vec_uniq<Floor>;
} // namespace Editor

namespace GraphicMap {
class VisibleGraphicLayer;
class BlockingGraphicLayer;
class EventsGraphicLayer;
class MapSceneLayer;

//////////////////////////////////////////////////////////////////////////////
//  MapGraphicsScene class
//////////////////////////////////////////////////////////////////////////////

class MapGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MapGraphicsScene(QObject* parent = nullptr);
    virtual ~MapGraphicsScene() override;

    void setFloors(const Editor::Floors& mapFloors, const QPixmap& chipset);
    void setPreview(const QPixmap& previewPix);
    void setSelection(const QRect& selectionRect);
    void drawGrid(quint16 width, quint16 height, unsigned int unit);

    void clearPreview();
    void clearSelection();
    void clearGrid();

    const vec_uniq<VisibleGraphicLayer>& graphicLayers() const;
    const vec_uniq<BlockingGraphicLayer>& blockingLayers() const;
    const vec_uniq<EventsGraphicLayer>& eventLayers() const;

    // void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    // void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    // void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

private:
    void instantiateFloor(Editor::Floor&, const QPixmap& chip, int& zIdxInOut);

    vec_uniq<VisibleGraphicLayer> m_visibleLayers;
    vec_uniq<BlockingGraphicLayer> m_blockingLayers;
    vec_uniq<EventsGraphicLayer> m_eventLayers;
    MapSceneLayer* m_currentGraphicLayer = nullptr;

    // QGraphicsScene deletes those
    std::vector<QGraphicsItem*> m_gridItems;
    QGraphicsRectItem* m_selectionRectItem = nullptr;
    QGraphicsPixmapItem* m_previewItem     = nullptr;
};

} // namespace GraphicMap

#endif // MAPGRAPHICSSCENE_H
