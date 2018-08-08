#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPen>

#include <utility>

#include "dummy/map.h"
#include "dummy/project.h"
#include "misc/mapdocument.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/selectiondrawingtool.h"


GraphicMap::SelectionDrawingTool::SelectionDrawingTool(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::DrawingTool(mapGraphicsScene), m_isSelecting(false),
      m_selectionItem(nullptr)
{

}

GraphicMap::SelectionDrawingTool::~SelectionDrawingTool()
{

}

void
GraphicMap::SelectionDrawingTool::onMousePress(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    m_isSelecting = true;
    m_selectionStart = mouseEvent->scenePos().toPoint();
}

void GraphicMap::SelectionDrawingTool::chipsetSelectionChanged(
    const QRect& selection)
{
    Q_UNUSED(selection);
}

void
GraphicMap::SelectionDrawingTool::onMouseMove(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_isSelecting)
    {
        QPoint pt(mouseEvent->scenePos().toPoint());
        QPoint topLeft, bottomRight;
        if (pt.x() < m_selectionStart.x() && pt.y() < m_selectionStart.y())
        {
            topLeft = pt;
            bottomRight = m_selectionStart;
        }
        else
        {
            topLeft = m_selectionStart;
            bottomRight = pt;
        }

        m_activeSelection.setTopLeft(
            QPoint(topLeft.x() - (topLeft.x() - 16),
                   topLeft.y() - (topLeft.y() - 16)));

        m_activeSelection.setBottomRight(
            QPoint(bottomRight.x() + (16 - (bottomRight.x() % 16)),
                   bottomRight.y() + (16 - (bottomRight.y() % 16))));


        if (nullptr != m_selectionItem)
        {
            m_mapGraphicScene.removeItem(m_selectionItem);
            m_selectionItem = nullptr;

        }

        m_selectionItem = m_mapGraphicScene.addRect(m_activeSelection,
                                                    QPen(Qt::green, 2));
    }
}

void
GraphicMap::SelectionDrawingTool::onMouseRelease(
    QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    m_isSelecting = false;
}

void GraphicMap::SelectionDrawingTool::onMouseLeave()
{
}
