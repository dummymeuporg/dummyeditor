#include "legacy/drawingtoolbarWidget.hpp"

#include <QAction>
#include <QActionGroup>
#include <QHBoxLayout>

#include "chipsetGraphicsScene.hpp"
#include "legacy/drawingTool/graphicPaletteTool.hpp"
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
    m_actions.clear();
}

void DrawingToolBarWidget::changeActiveLayer(
    GraphicMap::MapGraphicsScene* mapScene, const ChipsetGraphicsScene* chipset,
    std::vector<DrawingTools::DrawingTool*>& tools)
{
    // TODO check if previous layer is same type as new layer => don't unset +
    // reset
    mapScene->unsetDrawingTool();
    clear();

    m_actionGrp = std::unique_ptr<QActionGroup>(new QActionGroup(m_toolbar));

    for (auto* tool : tools) {
        std::unique_ptr<QAction> pAction(new QAction(this));
        pAction->setIcon(tool->icon());
        pAction->setText(tr("Tool"));
        pAction->setCheckable(true);
        m_actionGrp->addAction(pAction.get());

        // connect action to tool
        QObject::connect(pAction.get(), SIGNAL(triggered(bool)), //
                         tool, SLOT(setSelected(bool)));

        // connect tool to map
        QObject::connect(
            tool, SIGNAL(drawingToolSelected(::DrawingTools::DrawingTool*)),
            mapScene, SLOT(setDrawingTool(::DrawingTools::DrawingTool*)));

        // connect palette tool to chipset
        auto* paletteTool =
            dynamic_cast<DrawingTools::GraphicPaletteTool*>(tool);
        if (paletteTool != nullptr) {
            /*
              QObject::connect(
                  paletteTool,
                  SIGNAL(
                      drawingToolSelected(::DrawingTools::GraphicPaletteTool*)),
                  chipset,
                  SLOT(setPaletteTool(::DrawingTools::GraphicPaletteTool*)));
  */
        }

        m_actions.push_back(std::move(pAction));
    }

    m_toolbar->addActions(m_actionGrp->actions());

    // Select first tool
    if (m_actions.size() > 0) {
        m_actions[0]->trigger();
    }
}
