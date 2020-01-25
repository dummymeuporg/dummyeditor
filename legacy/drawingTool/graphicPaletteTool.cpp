#include "legacy/drawingTool/graphicPaletteTool.hpp"

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "chipsetGraphicsScene.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "utils/Logger.hpp"
#include "utils/definitions.hpp"

namespace DrawingTools {

GraphicPaletteTool::GraphicPaletteTool(
    QIcon&& icon, GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicGeneralTool(std::move(icon), mapGraphicsScene, visibleGraphicLayer)
{}

void GraphicPaletteTool::emitDrawingToolSelected()
{
    GraphicGeneralTool::emitDrawingToolSelected();
    Log::debug(tr("Emit drawing tool selected."));
    emit drawingToolSelected(this);
}

void GraphicPaletteTool::paletteMousePressEvent(
    const QGraphicsSceneMouseEvent* mouseEvent)
{}

void GraphicPaletteTool::paletteMouseMoveEvent(
    const QGraphicsSceneMouseEvent* mouseEvent)
{}

void GraphicPaletteTool::paletteMouseReleaseEvent(
    const QGraphicsSceneMouseEvent* mouseEvent)
{}

void GraphicPaletteTool::setSelection(const QRect& selection,
                                      const QPixmap& chipsetPixmap)
{
    m_rectSelection   = selection;
    m_selectionPixmap = chipsetPixmap.copy(selection);
    mapGraphScene().setPreview(chipsetPixmap.copy(selection));
}

void GraphicPaletteTool::setChipsetGraphicsScene(
    ChipsetGraphicsScene* chipsetGraphicsScene)
{
    m_chipsetGraphicsScene = chipsetGraphicsScene;
}

void GraphicPaletteTool::onUnselected()
{
    mapGraphScene().clearPreview();
}

} // namespace DrawingTools
