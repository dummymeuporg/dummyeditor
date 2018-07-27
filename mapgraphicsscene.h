#ifndef MAPGRAPHICSSCENE_H
#define MAPGRAPHICSSCENE_H

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

private:
    void _drawMap();
    void _drawLayer(const Dummy::Layer&);
    std::shared_ptr<Dummy::Map> m_map;
    QPixmap m_mapChipset;
};

#endif // MAPGRAPHICSSCENE_H
