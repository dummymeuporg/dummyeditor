#include "chipsetGraphicsScene.hpp"

#include <QGraphicsRectItem>

#include "utils/definitions.hpp"
#include "utils/Logger.hpp"
#include "drawingTool/graphicPaletteTool.hpp"

ChipsetGraphicsScene::ChipsetGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{}

void ChipsetGraphicsScene::drawGrid()
{
    QPen pen(Qt::black, 0.5);

    quint16 cellsWidth =
        static_cast<quint16>(m_chipset->boundingRect().width() / CELL_W);
    quint16 cellsHeight =
        static_cast<quint16>(m_chipset->boundingRect().height() / CELL_H);

    for (int x = 0; x <= cellsWidth * CELL_W; x += CELL_W) {
        QGraphicsItem* item = addLine(x, 0, x, cellsHeight * CELL_H, pen);
        item->setZValue(Z_GRID);
    }

    for (int y = 0; y <= cellsHeight * CELL_H; y += CELL_H) {
        QGraphicsItem* item = addLine(0, y, cellsWidth * CELL_W, y, pen);
        item->setZValue(Z_GRID);
    }
}

void ChipsetGraphicsScene::setChipset(const QPixmap& pixmap)
{
    clear();
    m_chipset = addPixmap(pixmap);
    drawGrid();
}

void ChipsetGraphicsScene::setSelection(const QRect& selection)
{
    m_currentSelection = selection;
    QPixmap selectionPixmap(m_chipset->pixmap().copy(m_currentSelection));
    emit selectionChanged(m_currentSelection, selectionPixmap);
}

void ChipsetGraphicsScene::setChipset(const QString& chipsetPath)
{
    Log::info(chipsetPath);
    setChipset(QPixmap(chipsetPath));
    setSelection(QRect(0, 0, 0, 0));
}

void ChipsetGraphicsScene::changeChipset(const QString& chipsetPath)
{
    setChipset(chipsetPath);
    emit chipsetChanged(chipsetPath);
}

void ChipsetGraphicsScene::mouseReleaseEvent(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    if (nullptr != m_paletteTool) {
        m_paletteTool->paletteMouseReleaseEvent(mouseEvent);
    }
}

void ChipsetGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    if (nullptr != m_paletteTool) {
        m_paletteTool->paletteMouseMoveEvent(mouseEvent);
    }
}

void ChipsetGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if (nullptr != m_paletteTool) {
        m_paletteTool->paletteMousePressEvent(mouseEvent);
    }
}

void ChipsetGraphicsScene::setPaletteTool(
    ::DrawingTools::GraphicPaletteTool* paletteTool)
{
    m_paletteTool = paletteTool;
    m_paletteTool->setChipsetGraphicsScene(this);
    Log::debug(tr("ChispetGraphicsScene: palette tool set!"));
}

void ChipsetGraphicsScene::unsetPaletteTool()
{
    m_paletteTool = nullptr;
    Log::debug(tr("Palette tool unset."));
}
