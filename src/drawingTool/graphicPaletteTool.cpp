#include "drawingTool/graphicPaletteTool.hpp"

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "chipsetGraphicsScene.hpp"
#include "utils/definitions.hpp"
#include "utils/Logger.hpp"

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
{
    if (nullptr == m_chipsetGraphicsScene
        || ! mouseEvent->buttons().testFlag(Qt::LeftButton) || m_isSelecting) {
        return;
    }

    m_isSelecting    = true;
    m_selectionStart = mouseEvent->scenePos().toPoint();

    if (m_selectionStart.x() >= m_chipsetGraphicsScene->width()
        || m_selectionStart.y() >= m_chipsetGraphicsScene->height()
        || m_selectionStart.x() < 0 || m_selectionStart.y() < 0) {
        return;
    }

    if (m_selectionRectItem != nullptr) {
        m_chipsetGraphicsScene->invalidate(m_selectionRectItem->rect());
        m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
    }

    // Add a square
    QBrush brush(QColor(66, 135, 245));
    int x = m_selectionStart.x() - (m_selectionStart.x() % CELL_W);
    int y = m_selectionStart.y() - (m_selectionStart.y() % CELL_H);
    setSelection(QRect(x, y, CELL_W, CELL_H),
                 m_chipsetGraphicsScene->chipset()->pixmap());
    m_selectionRectItem = m_chipsetGraphicsScene->addRect(m_rectSelection);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);
}

void GraphicPaletteTool::paletteMouseMoveEvent(
    const QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr == m_selectionRectItem || ! m_isSelecting) {
        return;
    }

    QPoint pt = mouseEvent->scenePos().toPoint();


    if (m_selectionRectItem != nullptr) {
        m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
        m_selectionRectItem = nullptr;
    }

    QBrush brush(QColor(66, 135, 245));

    // normalize selection rectangle in order accept any direction of selection
    QRect realRect = QRect(m_selectionStart, pt).normalized();

    // extend the rectangle to catch the complete border tiles
    realRect.setLeft(realRect.left() - (realRect.left() % CELL_W));
    realRect.setTop(realRect.top() - (realRect.top() % CELL_H));
    realRect.setRight(((realRect.right() / CELL_W) + 1) * CELL_W - 1);
    realRect.setBottom(((realRect.bottom() / CELL_H) + 1) * CELL_H - 1);

    setSelection(realRect, m_chipsetGraphicsScene->chipset()->pixmap());
    m_selectionRectItem = m_chipsetGraphicsScene->addRect(m_rectSelection);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);
}

void GraphicPaletteTool::paletteMouseReleaseEvent(
    const QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr != m_selectionItem) {
        m_isSelecting = false;
    }
}

void GraphicPaletteTool::setSelection(const QRect& selection,
                                      const QPixmap& chipsetPixmap)
{
    m_rectSelection   = selection;
    m_selectionPixmap = chipsetPixmap.copy(selection);
    m_selectionItem   = new ::QGraphicsPixmapItem(m_selectionPixmap);
}

void GraphicPaletteTool::setChipsetGraphicsScene(
    ChipsetGraphicsScene* chipsetGraphicsScene)
{
    m_chipsetGraphicsScene = chipsetGraphicsScene;
}

void GraphicPaletteTool::onUnselected()
{
    if (nullptr != m_chipsetGraphicsScene) {
        m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
        m_selectionItem = nullptr;
    }
}

} // namespace DrawingTools
