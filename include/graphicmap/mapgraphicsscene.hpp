#ifndef MAPGRAPHICSSCENE_H
#define MAPGRAPHICSSCENE_H

#include <memory>
#include <QGraphicsScene>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTool

namespace Editor {
class Map;
} // namespace Editor

namespace Dummy {
namespace Core {
class BlockingLayer;
} // namespace Core
} // namespace Dummy

namespace Misc {
class MapDocument;
}

namespace GraphicMap {
class GraphicLayer;
using GraphicLayers = std::vector<GraphicLayer*>;

//////////////////////////////////////////////////////////////////////////////
//  MapGraphicsScene class
//////////////////////////////////////////////////////////////////////////////

class MapGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MapGraphicsScene(QObject* parent = nullptr);
    virtual ~MapGraphicsScene() override;

    const std::shared_ptr<Editor::Map> map() const { return m_map; }
    const std::shared_ptr<Misc::MapDocument> mapDocument() const { return m_mapDocument; }
    const QRect& chipsetSelection() const { return m_chipsetSelection; }

    MapGraphicsScene& setMapDocument(
        const std::shared_ptr<Misc::MapDocument>& mapDocument);
    DrawingTools::DrawingTool* drawingTool() const { return m_drawingTool; }

    const GraphicLayers& graphicLayers() const { return m_graphicLayers; }

    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
    bool eventFilter(QObject*, QEvent*) override;
    void drawGrid(quint16 width, quint16 height, unsigned int unit);
    void clearGrid();
    void redrawGrid();

public slots:
    void changeMapDocument(
            const std::shared_ptr<Misc::MapDocument>& mapDocument
    );
    void unsetDrawingTool();
    void setDrawingTool(::DrawingTools::DrawingTool*);
    void adjustLayers() const;
    void setCurrentGraphicLayer(GraphicLayer*);

private:
    void cleanLayer(QVector<QGraphicsPixmapItem*>& layer);
    void drawMap();
    void drawGrid();
    void drawLayer(const Dummy::Core::BlockingLayer&);
    void setTile(QVector<QGraphicsPixmapItem*>& layer,
                  quint16 x,
                  quint16 y,
                  qint16 chipsetX,
                  qint16 chipsetY);
    void drawDarkFilter();

private:
    std::shared_ptr<Misc::MapDocument> m_mapDocument;
    std::shared_ptr<Editor::Map> m_map;
    QGraphicsRectItem* m_darkFilter;
    QPixmap m_mapChipset;
    QRect m_chipsetSelection;

    bool m_isDrawing;

    DrawingTools::DrawingTool* m_drawingTool;

    GraphicLayers m_graphicLayers;
    GraphicLayer* m_currentGraphicLayer;

    QVector<QGraphicsItem*> m_gridItems;
};

} // namespace GraphicMap

#endif // MAPGRAPHICSSCENE_H
