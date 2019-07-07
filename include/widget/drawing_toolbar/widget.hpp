#pragma once

#include <QWidget>

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

class Widget : public ::QWidget {
    Q_OBJECT
public:
    Widget(::QWidget* parent = nullptr);
    void reset(const GraphicMap::MapGraphicsScene*,
               const ::ChipsetGraphicsScene*,
               const std::vector<DrawingTool::DrawingTool*>&);
    void visit(DrawingTool::Graphic::GraphicTool&);
private:
    ::QToolBar* m_toolbar;
    ::QActionGroup* m_actionGroup;
};

} // namespace DrawingToolbar
} // namespace Widget
