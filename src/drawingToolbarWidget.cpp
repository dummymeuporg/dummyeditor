#include "drawingToolbarWidget.hpp"

#include <QAction>
#include <QActionGroup>
#include <QDebug>
#include <QHBoxLayout>

#include "chipsetGraphicsScene.hpp"
#include "drawingTool/blockingGeneralTool.hpp"
#include "drawingTool/graphicPen.hpp"
#include "drawingTool/graphicRectangle.hpp"
#include "graphicMap/layerGraphic.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

DrawingToolBarWidget::DrawingToolBarWidget(::QWidget* parent)
    : QWidget(parent)
    , m_toolbar(new QToolBar(this))
{
    // Set empty toolbar for the moment.
    setLayout(new QHBoxLayout());
    layout()->addWidget(m_toolbar);
}

void DrawingToolBarWidget::clear()
{
    m_toolbar->clear();

    if (m_actionGrp != nullptr) {
        delete m_actionGrp;
        m_actionGrp = nullptr;
    }
}

void DrawingToolBarWidget::reset()
{
    clear();

    if (m_drawingTools == nullptr)
        return;

    m_actionGrp = new QActionGroup(m_toolbar);

    for (auto* tool : *m_drawingTools) {
        auto* action = new QAction(this);
        action->setIcon(tool->icon());
        action->setText(tr("Tool"));
        action->setCheckable(true);
        m_actionGrp->addAction(action);

        QObject::connect(action, SIGNAL(triggered(bool)), tool,
                         SLOT(setSelected(bool)));

        QObject::connect(
            tool, SIGNAL(drawingToolSelected(::DrawingTools::DrawingTool*)),
            m_mapScene, SLOT(setDrawingTool(::DrawingTools::DrawingTool*)));

        tool->accept(*this);
    }

    m_toolbar->addActions(m_actionGrp->actions());
}

void DrawingToolBarWidget::onLayerSelected(
    const GraphicMap::MapGraphicsScene* mapScene,
    const ::ChipsetGraphicsScene* chipsetScene, GraphicMap::GraphicLayer& layer,
    std::vector<DrawingTools::DrawingTool*>* drawingTools)
{
    m_mapScene             = mapScene;
    m_chipsetGraphicsScene = chipsetScene;
    m_drawingTools         = drawingTools;

    layer.accept(*this);
}

void DrawingToolBarWidget::visitTool(DrawingTools::GraphicPen& pen)
{
    // XXX: connect the pen to the chipset scene.
    // m_chipsetScene
    qDebug() << "visitTool: connect tool.";
    QObject::connect(
        &pen, SIGNAL(drawingToolSelected(::DrawingTools::GraphicPaletteTool*)),
        m_chipsetGraphicsScene,
        SLOT(setPaletteTool(::DrawingTools::GraphicPaletteTool*)));
}

void DrawingToolBarWidget::visitTool(DrawingTools::GraphicRectangle& rectangle)
{
    qDebug() << "visitTool: connect tool.";
    QObject::connect(
        &rectangle,
        SIGNAL(drawingToolSelected(::DrawingTools::GraphicPaletteTool*)),
        m_chipsetGraphicsScene,
        SLOT(setPaletteTool(::DrawingTools::GraphicPaletteTool*)));
}

void DrawingToolBarWidget::visitTool(DrawingTools::GraphicEraser&)
{
    // Nothing to do!
}

void DrawingToolBarWidget::visitTool(DrawingTools::BlockingPen&)
{
    // Nothing to do!
}

void DrawingToolBarWidget::visitTool(DrawingTools::BlockingEraser&)
{
    // Nothing to do!
}

void DrawingToolBarWidget::visitTool(DrawingTools::SelectionTool&)
{
    // Nothing to do!
}

void DrawingToolBarWidget::visitGraphicLayer(
    GraphicMap::VisibleGraphicLayer& layer)
{
    DrawingTools::DrawingTool* tool = nullptr;

    switch (m_state) {
    case eToolBarState::Graphic:
        tool = mapScene()->drawingTool();
        if (nullptr != tool) {
            // TODO: clean this
            reinterpret_cast<DrawingTools::GraphicGeneralTool*>(tool)
                ->setVisibleGraphicLayer(&layer);
        }
        break;

    case eToolBarState::Blocking:
    case eToolBarState::NoDrawing:
    default: // keep default even if all values covereds wrong cast protection
        reset();
        setState(eToolBarState::Graphic);
        break;
    }
}

void DrawingToolBarWidget::visitGraphicLayer(
    GraphicMap::BlockingGraphicLayer& layer)
{
    DrawingTools::DrawingTool* tool = nullptr;

    switch (m_state) {
    case eToolBarState::Blocking:
        // TODO: clean this
        tool = mapScene()->drawingTool();
        if (nullptr != tool) {
            reinterpret_cast<DrawingTools::BlockingGeneralTool*>(tool)
                ->setBlockingGraphicLayer(&layer);
        }
        break;

    case eToolBarState::Graphic:
    case eToolBarState::NoDrawing:
    default: // keep default even if all values covereds wrong cast protection
        reset();
        setState(eToolBarState::Blocking);
        break;
    }
}

void DrawingToolBarWidget::setState(eToolBarState state)
{
    m_state = state;
}

void DrawingToolBarWidget::setInitialState()
{
    setState(eToolBarState::NoDrawing);
}
