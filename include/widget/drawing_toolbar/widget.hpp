#pragma once

#include <QWidget>
#include "drawing_tool/visitor.hpp"
#include "graphicmap/graphic_layer_visitor.hpp"

class QToolBar;
class QActionGroup;
class ChipsetGraphicsScene;

namespace GraphicMap {
class GraphicLayer;
class MapGraphicsScene;
class VisibleGraphicLayer;
class BlockingGraphicLayer;
} // namespace GraphicMap

namespace DrawingTool {
class DrawingTool;
namespace Graphic {
class GraphicTool;
} // namespace Graphic
} // namespace DrawingTool

namespace Widget {
namespace DrawingToolbar {

namespace State {
class State;
}

class Widget : public ::QWidget,
               public DrawingTool::Visitor,
               public GraphicMap::GraphicLayerVisitor {
    Q_OBJECT
public:
    Widget(::QWidget* parent = nullptr);
    void clear();
    void reset();
    void setState(std::shared_ptr<State::State>);
    void onLayerSelected(const GraphicMap::MapGraphicsScene*,
                         const ::ChipsetGraphicsScene*,
                         GraphicMap::GraphicLayer&,
                         std::vector<DrawingTool::DrawingTool*>*);

    const GraphicMap::MapGraphicsScene* mapScene() {
        return m_mapScene;
    }

    // DrawingTool::Visitor methods:
    void visitTool(DrawingTool::Graphic::Pen&) override;
    void visitTool(DrawingTool::Graphic::Rectangle&) override;
    void visitTool(DrawingTool::Graphic::Eraser&) override;
    void visitTool(DrawingTool::Blocking::Eraser&) override;
    void visitTool(DrawingTool::Blocking::Pen&) override;

    // GraphicMap::GraphicLayerVisitor methods:
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;



private:
    ::QToolBar* m_toolbar;
    ::QActionGroup* m_actionGroup;
    const ::ChipsetGraphicsScene* m_chipsetGraphicsScene;
    const GraphicMap::MapGraphicsScene* m_mapScene;
    std::vector<DrawingTool::DrawingTool*>* m_drawingTools;
    std::shared_ptr<State::State> m_state;
};

} // namespace DrawingToolbar
} // namespace Widget
