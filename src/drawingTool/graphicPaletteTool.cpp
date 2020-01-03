#include "drawingTool/graphicPaletteTool.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "chipsetgraphicsscene.hpp"

namespace DrawingTools {

GraphicPaletteTool::GraphicPaletteTool(
        QIcon&& icon,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicTool(std::move(icon), mapGraphicsScene, visibleGraphicLayer)
    , m_chipsetGraphicsScene(nullptr)
    , m_selectionRectItem(nullptr)
    , m_selectionItem(nullptr)
    , m_isSelecting(false)
{}

void GraphicPaletteTool::emitDrawingToolSelected() {
    GraphicTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void
GraphicPaletteTool::paletteMousePressEvent(::QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr == m_chipsetGraphicsScene
            || !mouseEvent->buttons().testFlag(Qt::LeftButton)
            || m_isSelecting){
        return;
    }

    m_isSelecting = true;
    m_selectionStart = mouseEvent->scenePos().toPoint();

    if (m_selectionStart.x() >= m_chipsetGraphicsScene->width()
            || m_selectionStart.y() >= m_chipsetGraphicsScene->height()
            || m_selectionStart.x() < 0
            || m_selectionStart.y() < 0) {
        return;
    }

    if (m_selectionRectItem != nullptr) {
        m_chipsetGraphicsScene->invalidate(m_selectionRectItem->rect());
        m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
    }

    // Add a square
    QBrush brush(QColor(66, 135, 245));
    int x = m_selectionStart.x() - (m_selectionStart.x() % 16);
    int y = m_selectionStart.y() - (m_selectionStart.y() % 16);
    setSelection(
        QRect(x, y, 16, 16),
        m_chipsetGraphicsScene->chipset()->pixmap()
    );
    m_selectionRectItem = m_chipsetGraphicsScene->addRect(m_rectSelection);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);
}

void GraphicPaletteTool::paletteMouseMoveEvent(
        QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr == m_selectionRectItem || !m_isSelecting) {
        return;
    }

    QPoint pt = mouseEvent->scenePos().toPoint();

    /*
    pt.setX(std::min(pt.x(), m_selectionItem->pixmap().width() - 16));
    pt.setY(std::min(pt.y(), m_selectionItem->pixmap().height() - 16));
    */
    pt.setX(pt.x() + (16 - (pt.x() % 16)));
    pt.setY(pt.y() + (16 - (pt.y() % 16)));


    if (m_selectionRectItem != nullptr) {
        m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
        m_selectionRectItem = nullptr;
    }

    QBrush brush(QColor(66, 135, 245));

    int x = m_selectionStart.x() - (m_selectionStart.x() % 16);
    int y = m_selectionStart.y() - (m_selectionStart.y() % 16);
    int xEnd = pt.x();
    int yEnd = pt.y();
    qDebug() << x << y << xEnd << yEnd;

    setSelection(
        QRect(x, y, xEnd - x, yEnd - y),
        m_chipsetGraphicsScene->chipset()->pixmap()
    );
    m_selectionRectItem = m_chipsetGraphicsScene->addRect(m_rectSelection);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);
}

void GraphicPaletteTool::paletteMouseReleaseEvent(
        QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr != m_selectionItem) {
        m_isSelecting = false;
    }
}

void GraphicPaletteTool::setSelection(
        const QRect& selection, const QPixmap& chipsetPixmap) {
    m_rectSelection = selection;
    m_selectionPixmap = chipsetPixmap.copy(selection);
    m_selectionItem = new ::QGraphicsPixmapItem(m_selectionPixmap);
}

void GraphicPaletteTool::setChipsetGraphicsScene(
        ChipsetGraphicsScene* chipsetGraphicsScene) {
    m_chipsetGraphicsScene = chipsetGraphicsScene;
}

void GraphicPaletteTool::onUnselected() {
    if (nullptr != m_chipsetGraphicsScene) {
        m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
        m_selectionItem = nullptr;
    }
}

void GraphicPaletteTool::onSelected() {
}

} // namespace DrawingTools
