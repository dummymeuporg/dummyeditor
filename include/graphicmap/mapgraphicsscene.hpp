#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include <cstdint>
#include <memory>
#include <vector>

class EditorProject;

namespace Dummy {
namespace Core {
class GraphicMap;
using BlockingLayer = std::vector<std::uint8_t>;

} // namespace Core
} // namespace Dummy

namespace Misc {
    class MapDocument;
}

class EditorMap;


namespace GraphicMap {

class DrawingTool;

class GraphicLayer;
class BlockingGraphicLayer;
class StartingPointLayer;
class VisibleGraphicLayer;
class MapSceneLayer;

class MapGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MapGraphicsScene(QObject* parent = nullptr);
    virtual ~MapGraphicsScene() override;

    inline const std::shared_ptr<EditorMap> map() const {
        return m_map;
    }

    inline const std::shared_ptr<Misc::MapDocument> mapDocument() const {
        return m_mapDocument;
    }

    inline VisibleGraphicLayer* firstLayer() const {
        return m_firstLayer;
    }

    inline VisibleGraphicLayer* secondLayer() const {
        return m_secondLayer;
    }

    inline VisibleGraphicLayer* thirdLayer() const {
        return m_thirdLayer;
    }

    inline VisibleGraphicLayer* fourthLayer() const {
        return m_fourthLayer;
    }

    inline BlockingGraphicLayer* blockingLayer() const
    {
        return m_blockingLayer;
    }

    inline StartingPointLayer* startingPointLayer() const
    {
        return m_startingPointLayer;
    }

    inline MapSceneLayer* activeLayer() const {
        return m_activeLayer;
    }

    inline const QRect& chipsetSelection() const {
        return m_chipsetSelection;
    }

    MapGraphicsScene& setPaitingTool(DrawingTool*);

    MapGraphicsScene& setMapDocument(
        const std::shared_ptr<Misc::MapDocument>& mapDocument);

    MapGraphicsScene& setActiveLayer(MapSceneLayer* layer) {
        m_activeLayer = layer;
        return *this;
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
        override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
        override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
        override;
    virtual void keyPressEvent(QKeyEvent*) override;
    virtual void keyReleaseEvent(QKeyEvent*) override;

    virtual bool eventFilter(QObject*, QEvent*) override;
public slots:
    void changeMapDocument(
        const std::shared_ptr<Misc::MapDocument>& mapDocument);
    void changeSelection(const QRect& selection);
    void setPenTool();
    void setRectangleTool();
    void setSelectionTool();

    void adjustLayers() const;

    /*
    const PaintingLayerState& paintingLayerState() const {
        return *m_paintingLayerState;
    }
    */

private:
    void _cleanLayer(QVector<QGraphicsPixmapItem*>& layer);
    void _drawMap();
    void _drawGrid();
    void _drawLayer(const Dummy::Core::BlockingLayer&);
    void _setTile(QVector<QGraphicsPixmapItem*>& layer,
                  quint16 x,
                  quint16 y,
                  qint16 chipsetX,
                  qint16 chipsetY);
    void _drawDarkFilter();

    std::shared_ptr<Misc::MapDocument> m_mapDocument;
    std::shared_ptr<EditorMap> m_map;
    QGraphicsRectItem* m_darkFilter;
    QPixmap m_mapChipset;
    QRect m_chipsetSelection;

    bool m_isDrawing;

    VisibleGraphicLayer* m_firstLayer;
    VisibleGraphicLayer* m_secondLayer;
    VisibleGraphicLayer* m_thirdLayer;
    VisibleGraphicLayer* m_fourthLayer;
    BlockingGraphicLayer* m_blockingLayer;
    MapSceneLayer* m_activeLayer; // Either 1st, 2nd or 3rd layer.
    StartingPointLayer* m_startingPointLayer;

    //PaintingLayerState* m_paintingLayerState;
    DrawingTool* m_drawingTool;


};

} // namespace GraphicMap
