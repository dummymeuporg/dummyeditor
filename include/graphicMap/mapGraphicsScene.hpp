#ifndef MAPGRAPHICSSCENE_H
#define MAPGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <memory>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////
template <typename T> using vec_uniq = std::vector<std::unique_ptr<T>>;

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTools

namespace Editor {
class Map;
} // namespace Editor

namespace Dummy {
namespace Core {
class BlockingLayer;
} // namespace Core
} // namespace Dummy

struct MapDocument;

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

    const std::shared_ptr<Editor::Map> map() const { return m_map; }
    const std::shared_ptr<MapDocument> mapDocument() const;
    DrawingTools::DrawingTool* drawingTool() const { return m_drawingTool; }
    const QRect& chipsetSelection() const { return m_chipsetSelection; }
    const vec_uniq<VisibleGraphicLayer>& graphicLayers() const;
    const vec_uniq<BlockingGraphicLayer>& blockingLayers() const;
    const vec_uniq<EventsGraphicLayer>& eventLayers() const;

    void setMapDocument(const std::shared_ptr<MapDocument>& mapDocument);

    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void drawGrid(quint16 width, quint16 height, unsigned int unit);
    void clearGrid();
    void redrawGrid();

public slots:
    void changeMapDocument(const std::shared_ptr<MapDocument>& mapDocument);
    void unsetDrawingTool();
    void setDrawingTool(::DrawingTools::DrawingTool*);
    void adjustLayers() const;
    void setCurrentGraphicLayer(MapSceneLayer*);

private:
    void cleanLayer(QVector<QGraphicsPixmapItem*>& layer);
    void drawMap();
    void drawGrid();
    void drawLayer(const Dummy::Core::BlockingLayer&);
    void setTile(QVector<QGraphicsPixmapItem*>& layer, quint16 x, quint16 y,
                 qint16 chipsetX, qint16 chipsetY);
    void drawDarkFilter();

private:
    std::shared_ptr<MapDocument> m_mapDocument;
    std::shared_ptr<Editor::Map> m_map;
    QGraphicsRectItem* m_darkFilter = nullptr;
    QPixmap m_mapChipset;
    QRect m_chipsetSelection;

    bool m_isDrawing = false;

    DrawingTools::DrawingTool* m_drawingTool = nullptr;

    MapSceneLayer* m_currentGraphicLayer = nullptr;

    vec_uniq<VisibleGraphicLayer> m_visibleLayers;
    vec_uniq<BlockingGraphicLayer> m_blockingLayers;
    vec_uniq<EventsGraphicLayer> m_eventLayers;

    QVector<QGraphicsItem*> m_gridItems;
};

} // namespace GraphicMap

#endif // MAPGRAPHICSSCENE_H
