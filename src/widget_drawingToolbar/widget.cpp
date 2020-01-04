#include "widget_drawingToolbar/widget.hpp"

#include <QDebug>
#include <QHBoxLayout>
#include <QToolBar>

#include "chipsetGraphicsScene.hpp"
#include "drawingTool/graphicPen.hpp"
#include "drawingTool/graphicRectangle.hpp"
#include "graphicMap/layerGraphic.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "widget_drawingToolbar/drawing_tool_action.hpp"
#include "widget_drawingToolbar/state_no_drawing_tools.hpp"

namespace DrawingToolbar {

Widget::Widget(::QWidget* parent)
    : QWidget(parent)
    , m_toolbar(new QToolBar(this))
    , m_actionGroup(new QActionGroup(m_toolbar))
    , m_chipsetGraphicsScene(nullptr)
    , m_mapScene(nullptr)
    , m_drawingTools(nullptr)
    , m_state(std::make_shared<NoDrawingToolState>(*this))
{
    // Set empty toolbar for the moment.
    setLayout(new QHBoxLayout());
    layout()->addWidget(m_toolbar);
}

void Widget::clear()
{
    layout()->removeWidget(m_toolbar);
    delete m_toolbar;
    m_toolbar = nullptr;
}

void Widget::onLayerSelected(
    const GraphicMap::MapGraphicsScene* mapScene,
    const ::ChipsetGraphicsScene* chipsetScene, GraphicMap::GraphicLayer& layer,
    std::vector<DrawingTools::DrawingTool*>* drawingTools)
{
    m_mapScene             = mapScene;
    m_chipsetGraphicsScene = chipsetScene;
    m_drawingTools         = drawingTools;

    layer.accept(*this);
}

void Widget::reset()
{
    clear();
    m_toolbar     = new QToolBar(this);
    m_actionGroup = new QActionGroup(m_toolbar);

    for (auto& tool : *m_drawingTools) {
        auto action(new DrawingToolAction(tool, this));
        action->setIcon(tool->icon());
        action->setText(tr("Tool"));
        action->setCheckable(true);
        m_actionGroup->addAction(action);

        QObject::connect(action, SIGNAL(triggered(bool)), action,
                         SLOT(setDrawingTool(bool)));
        QObject::connect(
            tool, SIGNAL(drawingToolSelected(::DrawingTools::DrawingTool*)),
            m_mapScene, SLOT(setDrawingTool(::DrawingTools::DrawingTool*)));
        tool->accept(*this);
    }
    m_toolbar->addActions(m_actionGroup->actions());
    layout()->addWidget(m_toolbar);
}

void Widget::visitTool(DrawingTools::GraphicPen& pen)
{
    // XXX: connect the pen to the chipset scene.
    // m_chipsetScene
    qDebug() << "visitTool: connect tool.";
    QObject::connect(
        &pen, SIGNAL(drawingToolSelected(::DrawingTools::GraphicPaletteTool*)),
        m_chipsetGraphicsScene,
        SLOT(setPaletteTool(::DrawingTools::GraphicPaletteTool*)));
}

void Widget::visitTool(DrawingTools::GraphicRectangle& rectangle)
{
    qDebug() << "visitTool: connect tool.";
    QObject::connect(
        &rectangle,
        SIGNAL(drawingToolSelected(::DrawingTools::GraphicPaletteTool*)),
        m_chipsetGraphicsScene,
        SLOT(setPaletteTool(::DrawingTools::GraphicPaletteTool*)));
}

void Widget::visitTool(DrawingTools::GraphicEraser&)
{
    // Nothing to do!
}

void Widget::visitTool(DrawingTools::BlockingPen&)
{
    // Nothing to do!
}

void Widget::visitTool(DrawingTools::BlockingEraser&)
{
    // Nothing to do!
}

void Widget::visitTool(DrawingTools::SelectionTool&)
{
    // Nothing to do!
}

void Widget::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer)
{
    m_state->visitGraphicLayer(layer);
}

void Widget::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer)
{
    m_state->visitGraphicLayer(layer);
}

void Widget::setState(std::shared_ptr<State> state)
{
    m_state = state;
}

void Widget::setInitialState()
{
    setState(std::make_shared<NoDrawingToolState>(*this));
}

} // namespace DrawingToolbar
