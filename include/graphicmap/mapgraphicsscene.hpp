#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include <cstdint>
#include <memory>
#include <vector>

namespace Editor {
class Project;
class Map;
} // namespace Editor

namespace Dummy {
namespace Core {
class GraphicMap;
class BlockingLayer;

} // namespace Core
} // namespace Dummy

namespace Misc {
    class MapDocument;
}

namespace GraphicMap {

class DrawingTool;
class GraphicLayer;
class BlockingGraphicLayer;
class StartingPointLayer;
class VisibleGraphicLayer;
class MapSceneLayer;

using GraphicLayers = std::vector<std::unique_ptr<GraphicLayer>>;

class MapGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MapGraphicsScene(QObject* parent = nullptr);
    virtual ~MapGraphicsScene() override;

    inline const std::shared_ptr<Editor::Map> map() const {
        return m_map;
    }

    inline const std::shared_ptr<Misc::MapDocument> mapDocument() const {
        return m_mapDocument;
    }

    inline const QRect& chipsetSelection() const {
        return m_chipsetSelection;
    }

    MapGraphicsScene& setPaitingTool(DrawingTool*);

    MapGraphicsScene& setMapDocument(
        const std::shared_ptr<Misc::MapDocument>& mapDocument);

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
    std::shared_ptr<Editor::Map> m_map;
    QGraphicsRectItem* m_darkFilter;
    QPixmap m_mapChipset;
    QRect m_chipsetSelection;

    bool m_isDrawing;

    //PaintingLayerState* m_paintingLayerState;
    DrawingTool* m_drawingTool;

    GraphicLayers m_graphicLayers;


};

} // namespace GraphicMap
