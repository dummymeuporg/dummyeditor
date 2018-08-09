#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include <memory>

namespace Dummy {
    class Layer;
    class Map;
}

namespace Misc {
    class MapDocument;
}


namespace GraphicMap {

    class DrawingTool;
    class GraphicLayer;
    class PaintingLayerState;
    class MapGraphicsScene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        MapGraphicsScene(QObject* parent = nullptr);
        virtual ~MapGraphicsScene();

        inline const std::shared_ptr<Dummy::Map>& map() const {
            return m_map;
        }

        inline const std::shared_ptr<Misc::MapDocument>& mapDocument() const {
            return m_mapDocument;
        }

        inline GraphicLayer* firstLayer() const {
            return m_firstLayer;
        }

        inline GraphicLayer* secondLayer() const {
            return m_secondLayer;
        }

        inline GraphicLayer* thirdLayer() const {
            return m_thirdLayer;
        }

        inline GraphicLayer* activeLayer() const {
            return m_activeLayer;
        }

        inline const QRect& chipsetSelection() const {
            return m_chipsetSelection;
        }

        MapGraphicsScene& setPaitingLayerState(PaintingLayerState*);
        MapGraphicsScene& setPaitingTool(DrawingTool*);

        MapGraphicsScene& setMapDocument(
            const std::shared_ptr<Misc::MapDocument>& mapDocument);

        MapGraphicsScene& setActiveLayer(GraphicLayer* layer) {
            m_activeLayer = layer;
            return *this;
        }

        virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

        virtual bool eventFilter(QObject*, QEvent*) override;
    public slots:
        void changeMapDocument(
            const std::shared_ptr<Misc::MapDocument>& mapDocument);
        void changeSelection(const QRect& selection);
        void showFirstLayer();
        void showSecondLayer();
        void showThirdLayer();

        void setPenTool();
        void setRectangleTool();
        void setSelectionTool();

    private:
        void _cleanLayer(QVector<QGraphicsPixmapItem*>& layer);
        void _drawMap();
        void _drawGrid();
        void _drawLayer(const Dummy::Layer&);
        void _setTile(QVector<QGraphicsPixmapItem*>& layer,
                      quint16 x,
                      quint16 y,
                      qint16 chipsetX,
                      qint16 chipsetY);
        void _drawDarkFilter();

        std::shared_ptr<Misc::MapDocument> m_mapDocument;
        std::shared_ptr<Dummy::Map> m_map;
        QGraphicsRectItem* m_darkFilter;
        QPixmap m_mapChipset;
        QRect m_chipsetSelection;

        bool m_isDrawing;

        GraphicLayer* m_firstLayer;
        GraphicLayer* m_secondLayer;
        GraphicLayer* m_thirdLayer;
        GraphicLayer* m_activeLayer; // Either 1st, 2nd or 3rd layer.

        PaintingLayerState* m_state;
        DrawingTool* m_drawingTool;


    };
}
