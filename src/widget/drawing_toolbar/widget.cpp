#include <QActionGroup>
#include <QToolBar>
#include <QHBoxLayout>

#include "drawing_tool/drawing_tool.hpp"

#include "drawing_tool/graphic/eraser.hpp"
#include "drawing_tool/graphic/pen.hpp"
#include "drawing_tool/graphic/rectangle.hpp"

#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/graphiclayer.hpp"
#include "chipsetgraphicsscene.hpp"

#include <QDebug>

#include "widget/drawing_toolbar/drawing_tool_action.hpp"
#include "widget/drawing_toolbar/widget.hpp"
#include "widget/drawing_toolbar/state/state.hpp"

#include "widget/drawing_toolbar/state/no_drawing_tools.hpp"
#include "widget/drawing_toolbar/state/display_blocking_tools.hpp"
#include "widget/drawing_toolbar/state/display_graphic_tools.hpp"


namespace Widget {
namespace DrawingToolbar {

Widget::Widget(::QWidget* parent) :
    QWidget(parent),
    m_toolbar(new QToolBar(this)),
    m_actionGroup(new QActionGroup(m_toolbar)),
    m_chipsetGraphicsScene(nullptr),
    m_mapScene(nullptr),
    m_state(std::make_shared<State::NoDrawingTools>(*this))
{
    // Set empty toolbar for the moment.
    setLayout(new QHBoxLayout());
    layout()->addWidget(m_toolbar);
}

void Widget::clear() {
    layout()->removeWidget(m_toolbar);
    delete m_toolbar;
    m_toolbar = nullptr;
}

void
Widget::onLayerSelected(
    const GraphicMap::MapGraphicsScene* mapScene,
    const ::ChipsetGraphicsScene* chipsetScene,
    GraphicMap::GraphicLayer& layer,
    std::vector<DrawingTool::DrawingTool*>* drawingTools)
{
    clear();
    m_mapScene = mapScene;
    m_chipsetGraphicsScene = chipsetScene;
    m_drawingTools = drawingTools;

    layer.accept(*this);
}

void Widget::reset() {
    m_toolbar = new QToolBar(this);
    m_actionGroup = new QActionGroup(m_toolbar);

    for (auto& tool: *m_drawingTools) {
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
            tool,
            SIGNAL(drawingToolSelected(::DrawingTool::DrawingTool*)),
            m_mapScene,
            SLOT(setDrawingTool(::DrawingTool::DrawingTool*))
        );
        tool->accept(*this);

    }
    m_toolbar->addActions(m_actionGroup->actions());
    layout()->addWidget(m_toolbar);
}

void Widget::visitTool(DrawingTool::Graphic::Pen& pen) {
    // XXX: connect the pen to the chipset scene.
    // m_chipsetScene
    qDebug() << "visitTool: connect tool.";
    QObject::connect(
        &pen,
        SIGNAL(drawingToolSelected(::DrawingTool::Graphic::PaletteTool*)),
        m_chipsetGraphicsScene,
        SLOT(setPaletteTool(::DrawingTool::Graphic::PaletteTool*))
    );
}

void Widget::visitTool(DrawingTool::Graphic::Rectangle& rectangle) {
    qDebug() << "visitTool: connect tool.";
    QObject::connect(
        &rectangle,
        SIGNAL(drawingToolSelected(::DrawingTool::Graphic::PaletteTool*)),
        m_chipsetGraphicsScene,
        SLOT(setPaletteTool(::DrawingTool::Graphic::PaletteTool*))
    );
}

void Widget::visitTool(DrawingTool::Graphic::Eraser&) {
    // Nothing to do!
}

void Widget::visitTool(DrawingTool::Blocking::Pen&) {
    // Nothing to do!
}

void Widget::visitTool(DrawingTool::Blocking::Eraser&) {
    // Nothing to do!
}

void Widget::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    m_state->visitGraphicLayer(layer);
}

void Widget::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {
    m_state->visitGraphicLayer(layer);
}

void Widget::setState(std::shared_ptr<State::State> state) {
    m_state = state;
}

} // namespace DrawingToolbar
} // namespace Widget
