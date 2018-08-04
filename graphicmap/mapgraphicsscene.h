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

    class GraphicLayer;
    class MapGraphicsScene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        MapGraphicsScene(QObject* parent = nullptr);

        inline const std::shared_ptr<Dummy::Map>& map() const {
            return m_map;
        }

        inline const std::shared_ptr<Misc::MapDocument>& mapDocument() const {
            return m_mapDocument;
        }

        MapGraphicsScene& setMapDocument(
            const std::shared_ptr<Misc::MapDocument>& mapDocument);

        virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    public slots:
        void changeMapDocument(
            const std::shared_ptr<Misc::MapDocument>& mapDocument);
        void changeSelection(const QRect& selection);
        void showFirstLayer();
        void showSecondLayer();
        void showThirdLayer();
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

        int m_currentLayer;
        GraphicLayer* m_activeLayer; // Either 1st, 2nd or 3rd layer.

        QGraphicsRectItem* m_darkFilterOne; // Between 1st and 2nd layer
        QGraphicsRectItem* m_darkFilterTwo; // Between 2nd and 3rd layer


    };
}
