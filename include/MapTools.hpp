#ifndef MAPTOOLS_H
#define MAPTOOLS_H

#include <QPixmap>
#include <QRect>
#include <cstdint>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Ui {
class GeneralWindow;
}

namespace GraphicMap {
class MapGraphicsScene;
class EventGraphicLayer;
class VisibleGraphicLayer;
class BlockingGraphicLayer;
} // namespace GraphicMap

class ChipsetGraphicsScene;

//////////////////////////////////////////////////////////////////////////////
//  MapTools class
//////////////////////////////////////////////////////////////////////////////

class MapTools
{
public:
    explicit MapTools(ChipsetGraphicsScene&, GraphicMap::MapGraphicsScene&, Ui::GeneralWindow&);

    void clear();

    void setActiveLayer(GraphicMap::VisibleGraphicLayer*);
    void setActiveLayer(GraphicMap::BlockingGraphicLayer*);
    void setActiveLayer(GraphicMap::EventGraphicLayer*);

    void setPen();
    void setEraser();
    void setSelectTool();
    void setPasteTool();

    void setGrid(bool gridVisible = true);
    void updateGridDisplay();

    void previewTool(const QRect& clickingRegion);
    void useTool(const QRect& clickingRegion);

private:
    void resetTools();
    void resetLayerLink();

    QPoint adjustOnGrid(const QPoint& pxCoords);
    QRect adjustOnGrid(const QRect& rawRect);
    void forceInScene(QPoint& point); // set the point in the scene if it's out

    QPixmap previewVisible(const QRect&);

    void drawBlocking(const QRect&);
    void drawVisible(const QRect&);

    void eraseBlocking(const QRect&);
    void eraseVisible(const QRect&);


    enum class eLayerType
    {
        None,
        Visible,
        Blocking,
        Event,
    };

    enum class eTools
    {
        Pen,
        Eraser,
        Selection,
        Paste,
    };

    const ChipsetGraphicsScene& m_chipsetScene;
    GraphicMap::MapGraphicsScene& m_mapScene;
    Ui::GeneralWindow& m_toolsUI;

    eTools m_currMode                              = eTools::Pen;
    eLayerType m_currLayerType                     = eLayerType::None;
    GraphicMap::VisibleGraphicLayer* m_visLayer    = nullptr;
    GraphicMap::BlockingGraphicLayer* m_blockLayer = nullptr;
    GraphicMap::EventGraphicLayer* m_eventLayer    = nullptr;

    uint16_t m_uiLayerW   = 0;
    uint16_t m_uiLayerH   = 0;
    uint32_t m_uiGridStep = 0;
};

#endif // MAPTOOLS_H
