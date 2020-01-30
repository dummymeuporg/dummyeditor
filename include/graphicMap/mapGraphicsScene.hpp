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

class MapTools;

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
    void setPreview(const QPixmap& previewPix, const QPoint& pos);
    void setSelectRect(const QRect& selectionRect);
    void drawGrid(quint16 width, quint16 height, unsigned int unit);
    void linkToolSet(MapTools* tools) { m_tools = tools; }

    QRectF selectionRectItem();

    void clearPreview();
    void clearSelectRect();
    void clearGrid();

    const vec_uniq<VisibleGraphicLayer>& graphicLayers() const;
    const vec_uniq<BlockingGraphicLayer>& blockingLayers() const;
    const vec_uniq<EventsGraphicLayer>& eventLayers() const;

    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

public slots:
    void clear();

private:
    void instantiateFloor(Editor::Floor&, const QPixmap& chip, int& zIdxInOut);

    // Layers
    vec_uniq<VisibleGraphicLayer> m_visibleLayers;
    vec_uniq<BlockingGraphicLayer> m_blockingLayers;
    vec_uniq<EventsGraphicLayer> m_eventLayers;

    // Tools
    MapTools* m_tools = nullptr;
    QPoint m_firstClickPt;
    bool m_isUsingTool = false;

    // QGraphicsScene deletes those
    vec_uniq<QGraphicsItem> m_gridItems;
    std::unique_ptr<QGraphicsRectItem> m_selectionRectItem;
    std::unique_ptr<QGraphicsPixmapItem> m_previewItem;
};

} // namespace GraphicMap

#endif // MAPGRAPHICSSCENE_H
