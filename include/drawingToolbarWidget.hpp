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
class GraphicLayer;
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTools

//////////////////////////////////////////////////////////////////////////////
//  DrawingToolbarWidget class
//////////////////////////////////////////////////////////////////////////////

class DrawingToolBarWidget : public QWidget, public DrawingTools::DrawingVisitor
{
    Q_OBJECT
public:
    explicit DrawingToolBarWidget(QWidget* parent = nullptr);

    void clear();
    void reset();

    const GraphicMap::MapGraphicsScene* mapScene() { return m_mapScene; }

    // DrawingTool::Visitor methods:
    void visitTool(DrawingTools::GraphicPen&) override;
    void visitTool(DrawingTools::GraphicRectangle&) override;
    void visitTool(DrawingTools::GraphicEraser&) override;
    void visitTool(DrawingTools::BlockingEraser&) override;
    void visitTool(DrawingTools::BlockingPen&) override;
    void visitTool(DrawingTools::SelectionTool&) override;

    void changeActiveLayer(GraphicMap::MapGraphicsScene*,
                           const ChipsetGraphicsScene* chipset,
                           GraphicMap::GraphicLayer* layer,
                           std::vector<DrawingTools::DrawingTool*>*);

private:
    QToolBar* m_toolbar       = nullptr;
    QActionGroup* m_actionGrp = nullptr;

    const ChipsetGraphicsScene* m_chipsetGraphicsScene      = nullptr;
    const GraphicMap::MapGraphicsScene* m_mapScene          = nullptr;
    std::vector<DrawingTools::DrawingTool*>* m_currentTools = nullptr;
};

#endif // DRAWINGTOOLBARWIDGET_H
