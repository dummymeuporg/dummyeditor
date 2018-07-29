#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include <memory>

namespace Dummy {
    class Layer;
    class Map;
}

class MapGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MapGraphicsScene(QObject* parent = nullptr);

    inline const std::shared_ptr<Dummy::Map>& map() const {
        return m_map;
    }

    MapGraphicsScene& setMap(const std::shared_ptr<Dummy::Map>& map);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
public slots:
    void changeMap(const std::shared_ptr<Dummy::Map>& map);
    void changeSelection(const QRect& selection);
private:
    void _drawMap();
    void _drawGrid();
    void _drawLayer(const Dummy::Layer&);

    std::shared_ptr<Dummy::Map> m_map;
    QPixmap m_mapChipset;
    QRect m_chipsetSelection;
};
