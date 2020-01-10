#ifndef MAPSCENELAYER_H
#define MAPSCENELAYER_H

#include <QObject>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class MapGraphicsScene;

//////////////////////////////////////////////////////////////////////////////
//  GraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class MapSceneLayer : public QObject
{
    Q_OBJECT
public:
    MapSceneLayer(MapGraphicsScene&, int zIndex);
    virtual ~MapSceneLayer();

    //virtual MapSceneLayer& removeTile(quint16, quint16) = 0;

protected:
    MapGraphicsScene& m_mapGraphicsScene;
    int m_zIndex;
};
} // namespace GraphicMap

#endif // MAPSCENELAYER_H
