#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include <utility>

#include "dummy/map.h"
#include "dummy/project.h"
#include "misc/mapdocument.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/rectangledrawingtool.h"


GraphicMap::RectangleDrawingTool::RectangleDrawingTool(
    GraphicMap::MapGraphicsScene& mapGraphicScene)
    : GraphicMap::DrawingTool(mapGraphicScene), m_selectionItem(nullptr),
      m_mouseCliked(false), m_rectChipsetSelection(0, 0, 0, 0),
      m_rectangle(0, 0, 0, 0)
{

}

GraphicMap::RectangleDrawingTool::~RectangleDrawingTool() {

}

void
GraphicMap::RectangleDrawingTool::onMousePress(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_rectChipsetSelection.size() == QSize(0, 0))
    {
        return;
    }
    m_mouseCliked = true;
    //m_selectionItem = new QGraphicsPixmapItem()
    QPoint pt(mouseEvent->scenePos().toPoint());

    // Translate the coordinate to get the top upper corner of the tile.
    pt.setX(pt.x() - (pt.x() % 16));
    pt.setY(pt.y() - (pt.y() % 16));

    m_rectangle.setTopLeft(pt);
    m_rectangle.setSize(QSize(16, 16));

    _drawChipsetSelectionInRectangle();
    m_selectionItem->setPos(QPoint(m_rectangle.topLeft()));
    m_selectionItem->setZValue(100);
    m_mapGraphicScene.addItem(m_selectionItem);

}

void GraphicMap::RectangleDrawingTool::chipsetSelectionChanged(
    const QRect& selection)
{
    m_rectChipsetSelection = selection;
    std::shared_ptr<Dummy::Map> map(
        m_mapGraphicScene.mapDocument()->map());

    // XXX: Ugly
    QPixmap chipsetPixmap(
        m_mapGraphicScene.mapDocument()->project().fullpath() + "/chipsets/" +
        map->chipset());

    m_pixmapChipsetSelection = chipsetPixmap.copy(selection);
    qDebug() << "Selection size: " << m_rectChipsetSelection.size();
}


void
GraphicMap::RectangleDrawingTool::onMouseMove(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_rectChipsetSelection.size() == QSize(0, 0))
    {
        return;
    }

    if (m_mouseCliked)
    {
        QPoint pt(mouseEvent->scenePos().toPoint());
        pt.setX(pt.x() + (15 - (pt.x() % 16)));
        pt.setY(pt.y() + (15 - (pt.y() % 16)));
        qDebug() << m_rectangle;
        m_rectangle.setBottomRight(pt);

        m_mapGraphicScene.removeItem(m_selectionItem);
        _drawChipsetSelectionInRectangle();
        qDebug() << m_selectionItem;
        m_selectionItem->setPos(QPoint(m_rectangle.topLeft()));
        m_selectionItem->setZValue(100);
        m_mapGraphicScene.addItem(m_selectionItem);
    }
}

void
GraphicMap::RectangleDrawingTool::onMouseRelease(
    QGraphicsSceneMouseEvent* event)
{
    m_mouseCliked = false;
    m_rectangle = QRect(0, 0, 0, 0);
}

void GraphicMap::RectangleDrawingTool::onMouseLeave()
{

}

void
GraphicMap::RectangleDrawingTool::_drawChipsetSelectionInRectangle()
{
    if (m_pixmapChipsetSelection.size() == QSize(0, 0))
    {
        return;
    }

    QPixmap dstPixmap(m_rectangle.size());
    QPainter painter(&dstPixmap);

    for (int j = 0;
         j < m_rectangle.height();
         j += m_pixmapChipsetSelection.height())
    {
        for (int i = 0;
             i < m_rectangle.width();
             i += m_pixmapChipsetSelection.width())
        {
            painter.drawPixmap(
                QRect(i, j, m_pixmapChipsetSelection.width(),
                      m_pixmapChipsetSelection.height()),
                m_pixmapChipsetSelection);
        }
    }
    if (nullptr != m_selectionItem) {
        m_mapGraphicScene.removeItem(m_selectionItem);
    }
    m_selectionItem = new QGraphicsPixmapItem(dstPixmap);
}
