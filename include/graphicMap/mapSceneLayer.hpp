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

    MapGraphicsScene& mapGraphicsScene() { return m_mapGraphicsScene; }

    // virtual MapSceneLayer& removeTile(quint16, quint16) = 0;

protected:
    int zIndex() { return m_zIndex; }

private:
    MapGraphicsScene& m_mapGraphicsScene;
    int m_zIndex;
};
} // namespace GraphicMap

#endif // MAPSCENELAYER_H
