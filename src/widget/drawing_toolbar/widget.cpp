#include <QActionGroup>
#include <QToolBar>
#include <QHBoxLayout>

#include "drawing_tool/drawing_tool.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "chipsetgraphicsscene.hpp"

#include "widget/drawing_toolbar/drawing_tool_action.hpp"
#include "widget/drawing_toolbar/widget.hpp"


namespace Widget {
namespace DrawingToolbar {

Widget::Widget(::QWidget* parent) :
    QWidget(parent),
    m_toolbar(new QToolBar(this)),
    m_actionGroup(new QActionGroup(m_toolbar))
{
    // Set empty toolbar for the moment.
    setLayout(new QHBoxLayout());
    layout()->addWidget(m_toolbar);
}

void
Widget::reset(const GraphicMap::MapGraphicsScene* mapScene,
              const ::ChipsetGraphicsScene* chipsetGraphicScene,
              const std::vector<DrawingTool::DrawingTool*>& drawingTools) {
    layout()->removeWidget(m_toolbar);
    delete m_toolbar;



    m_toolbar = new QToolBar(this);
    m_actionGroup = new QActionGroup(m_toolbar);

    for (auto& tool: drawingTools) {
        auto action(new DrawingToolAction(tool, this));
        action->setIcon(tool->icon());
        action->setText(tr("Tool"));
        action->setCheckable(true);
        m_actionGroup->addAction(action);

        QObject::connect(
            action,
            SIGNAL(triggered(bool)),
            action,
            SLOT(setDrawingTool(bool))
        );
        QObject::connect(
            action,
            SIGNAL(trigerred(DrawingTool::DrawingTool*)),
            mapScene,
            SLOT(setDrawingTool(DrawingTool::DrawingTool*))
        );
    }
    m_toolbar->addActions(m_actionGroup->actions());
    layout()->addWidget(m_toolbar);
}

void Widget::visit(DrawingTool::Graphic::GraphicTool& graphicTool) {
    // Connect the graphic tool to the
}

} // namespace DrawingToolbar
} // namespace Widget
