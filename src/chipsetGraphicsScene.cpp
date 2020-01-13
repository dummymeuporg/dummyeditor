#include "chipsetGraphicsScene.hpp"

#include <QDebug>
#include <QGraphicsRectItem>

#include "drawingTool/graphicPaletteTool.hpp"

ChipsetGraphicsScene::ChipsetGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
    , m_chipset(nullptr)
    , m_paletteTool(nullptr)
{}

void ChipsetGraphicsScene::drawGrid()
{
    QPen pen(Qt::black, 0.5);

    quint16 cellsWidth =
        static_cast<quint16>(m_chipset->boundingRect().width() / 16);
    quint16 cellsHeight =
        static_cast<quint16>(m_chipset->boundingRect().height() / 16);

    for (int i = 0; i <= cellsWidth; i++) {
        QGraphicsItem* item = addLine(i * 16, 0, i * 16, cellsHeight * 16, pen);
        item->setZValue(99);
    }

    for (int i = 0; i <= cellsHeight; i++) {
        QGraphicsItem* item = addLine(0, i * 16, cellsWidth * 16, i * 16, pen);
        item->setZValue(99);
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
    qDebug() << chipsetPath;
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
    qDebug() << "ChispetGraphicsScene: palette tool set!";
}

void ChipsetGraphicsScene::unsetPaletteTool()
{
    m_paletteTool = nullptr;
    qDebug() << "Palette tool unset.";
}
