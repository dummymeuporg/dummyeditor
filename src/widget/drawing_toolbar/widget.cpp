#include <QActionGroup>
#include <QToolBar>
#include <QHBoxLayout>

#include "drawing_tool/drawing_tool.hpp"
#include "drawing_tool/graphic/pen.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "chipsetgraphicsscene.hpp"

#include "widget/drawing_toolbar/drawing_tool_action.hpp"
#include "widget/drawing_toolbar/widget.hpp"


namespace Widget {
namespace DrawingToolbar {

Widget::Widget(::QWidget* parent) :
    QWidget(parent),
    m_toolbar(new QToolBar(this)),
    m_actionGroup(new QActionGroup(m_toolbar)),
    m_chipsetGraphicsScene(nullptr)
{
    // Set empty toolbar for the moment.
    setLayout(new QHBoxLayout());
    layout()->addWidget(m_toolbar);
}

void
Widget::reset(const GraphicMap::MapGraphicsScene* mapScene,
              const ::ChipsetGraphicsScene* chipsetScene,
              const std::vector<DrawingTool::DrawingTool*>& drawingTools) {
    layout()->removeWidget(m_toolbar);
    delete m_toolbar;

    m_chipsetGraphicsScene = chipsetScene;

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

        QObject::connect(
            action,
            SIGNAL(trigerred(bool)),
            action,
            SLOT(setDrawingTool(bool))
        );

    }
    m_toolbar->addActions(m_actionGroup->actions());
    layout()->addWidget(m_toolbar);
}

void Widget::visitTool(DrawingTool::Graphic::Pen& pen) {
    // XXX: connect the pen to the chipset scene.
    // m_chipsetScene
    QObject::connect(
        &pen,
        SIGNAL(trigerred(DrawingTool::GraphicTool*)),
        m_chipsetGraphicsScene,
        SLOT(setGraphicTool(DrawingTool::GraphicTool*))
    );

}

} // namespace DrawingToolbar
} // namespace Widget
