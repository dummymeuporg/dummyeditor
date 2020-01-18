#include "drawingToolbarWidget.hpp"

#include <QAction>
#include <QActionGroup>
#include <QDebug>
#include <QHBoxLayout>

#include "chipsetGraphicsScene.hpp"
#include "drawingTool/blockingEraser.hpp"
#include "drawingTool/blockingGeneralTool.hpp"
#include "drawingTool/blockingPen.hpp"
#include "drawingTool/drawingSelection.hpp"
#include "drawingTool/graphicPen.hpp"
#include "drawingTool/graphicRectangle.hpp"
#include "graphicMap/layerGraphic.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
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
    // Todo follow leaks of QActions?

    if (m_actionGrp != nullptr) {
        delete m_actionGrp;
        m_actionGrp = nullptr;
    }
}

void DrawingToolBarWidget::reset()
{
    clear();

    if (m_currentTools == nullptr)
        return;

    m_actionGrp = new QActionGroup(m_toolbar);

    for (auto* tool : *m_currentTools) {
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

        // TODO a more specific call to avoid this dynamic cast, but without the
        // complexity of visitor pattern
        // or connect to a more general slot
        auto* paletteTool =
            dynamic_cast<DrawingTools::GraphicPaletteTool*>(tool);

        if (paletteTool != nullptr) {
            QObject::connect(
                paletteTool,
                SIGNAL(
                    drawingToolSelected(::DrawingTools::GraphicPaletteTool*)),
                m_chipsetGraphicsScene,
                SLOT(setPaletteTool(::DrawingTools::GraphicPaletteTool*)));
        }
    }

    m_toolbar->addActions(m_actionGrp->actions());
}

void DrawingToolBarWidget::changeActiveLayer(
    GraphicMap::MapGraphicsScene* mapScene, const ChipsetGraphicsScene* chipset,
    std::vector<DrawingTools::DrawingTool*>* tools)
{
    m_mapScene             = mapScene;
    m_chipsetGraphicsScene = chipset;
    m_currentTools         = tools;

    mapScene->unsetDrawingTool();
    reset();

    // TODO check if previous layer is same type as new layer => don't unset +
    // reset

    // TODO select first tool (and not just mapScene->select, but the button in
    // ui also need to be checked
}
