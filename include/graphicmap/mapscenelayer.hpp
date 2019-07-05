#pragma once

#include <QObject>

namespace GraphicMap {
class MapGraphicsScene;
class MapSceneLayer : public ::QObject
{
    Q_OBJECT
public:
    MapSceneLayer(MapGraphicsScene&, int zIndex);
    virtual ~MapSceneLayer();

    virtual MapSceneLayer& removeTile(quint16, quint16) = 0;
protected:
    MapGraphicsScene& m_mapGraphicsScene;
    int m_zIndex;
};
} // namespace MapSceneLayer
