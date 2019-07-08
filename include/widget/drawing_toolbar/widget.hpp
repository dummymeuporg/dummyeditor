#pragma once

#include <QWidget>
#include "drawing_tool/visitor.hpp"

class QToolBar;
class QActionGroup;
class ChipsetGraphicsScene;

namespace GraphicMap {
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTool {
class DrawingTool;
namespace Graphic {
class GraphicTool;
} // namespace Graphic
} // namespace DrawingTool

namespace Widget {
namespace DrawingToolbar {

class Widget : public ::QWidget,
               public DrawingTool::Visitor {
    Q_OBJECT
public:
    Widget(::QWidget* parent = nullptr);
    void reset(const GraphicMap::MapGraphicsScene*,
               const ::ChipsetGraphicsScene*,
               const std::vector<DrawingTool::DrawingTool*>&);
    void visitTool(DrawingTool::Graphic::Pen&) override;
private:
    ::QToolBar* m_toolbar;
    ::QActionGroup* m_actionGroup;
    const ::ChipsetGraphicsScene* m_chipsetGraphicsScene;
};

} // namespace DrawingToolbar
} // namespace Widget
