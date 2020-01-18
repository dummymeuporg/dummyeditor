#ifndef DRAWINGTOOLBARWIDGET_H
#define DRAWINGTOOLBARWIDGET_H

#include <QToolBar>

#include "drawingTool/blockingGeneralTool.hpp"
#include "drawingTool/drawingVisitor.hpp"
#include "drawingTool/graphicGeneralTool.hpp"
#include "graphicMap/graphicLayerVisitor.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class ChipsetGraphicsScene;
class QActionGroup;

namespace GraphicMap {
class MapSceneLayer;
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTools

//////////////////////////////////////////////////////////////////////////////
//  DrawingToolbarWidget class
//////////////////////////////////////////////////////////////////////////////

class DrawingToolBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingToolBarWidget(QWidget* parent = nullptr);

    void clear();
    void reset();

    const GraphicMap::MapGraphicsScene* mapScene() { return m_mapScene; }

    void changeActiveLayer(GraphicMap::MapGraphicsScene*,
                           const ChipsetGraphicsScene* chipset,
                           std::vector<DrawingTools::DrawingTool*>*);

private:
    QToolBar* m_toolbar       = nullptr;
    QActionGroup* m_actionGrp = nullptr;

    const ChipsetGraphicsScene* m_chipsetGraphicsScene      = nullptr;
    const GraphicMap::MapGraphicsScene* m_mapScene          = nullptr;
    std::vector<DrawingTools::DrawingTool*>* m_currentTools = nullptr;
};

#endif // DRAWINGTOOLBARWIDGET_H
