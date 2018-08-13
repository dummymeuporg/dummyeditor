#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>
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
    if (mouseEvent->buttons() & Qt::LeftButton) {
        m_isSelecting = true;
        m_selectionStart = mouseEvent->scenePos().toPoint();

        QPen pen(Qt::red, 2);
        m_selectionStart.setX(
            m_selectionStart.x() - (m_selectionStart.x() % 16));
        m_selectionStart.setY(
            m_selectionStart.y() - (m_selectionStart.y() % 16));
        m_activeSelection = QRect(m_selectionStart.x(),
                                  m_selectionStart.y(),
                                  16,
                                  16);

        if (nullptr != m_selectionItem)
        {
            m_mapGraphicScene.removeItem(m_selectionItem);
            m_selectionItem = nullptr;

        }

        m_selectionItem = m_mapGraphicScene.addRect(m_activeSelection,
                                                    pen);
        m_selectionItem->setZValue(10);
        qDebug() << "SelectionTool is selecting." << m_activeSelection;
    }
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

        if (nullptr != m_selectionItem)
        {
            m_mapGraphicScene.removeItem(m_selectionItem);
            m_selectionItem = nullptr;

        }
        int x = m_selectionStart.x() - (m_selectionStart.x() % 16);
        int y = m_selectionStart.y() - (m_selectionStart.y() % 16);
        int xEnd = pt.x() + (16 - (pt.x() % 16));
        int yEnd = pt.y() + (16 - (pt.y() % 16));

        m_activeSelection = QRect(x, y, xEnd - x, yEnd - y);

        m_selectionItem = m_mapGraphicScene.addRect(m_activeSelection,
                                                    QPen(Qt::red, 2));
        m_selectionItem->setZValue(10);
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

void GraphicMap::SelectionDrawingTool::onKeyPress(QKeyEvent* event)
{

    if (0 != (event->modifiers() & Qt::ControlModifier))
    {
        switch(event->key())
        {
        case Qt::Key_X:
            qDebug() << "Cut in selection tool.";
            break;
        case Qt::Key_C:
            qDebug() << "Copy in selection tool.";
            break;
        case Qt::Key_V:
            qDebug() << "Paste in selection tool.";
            break;
        }
    }
    else if (event->key() == Qt::Key_Delete)
    {
        qDebug() << "Delete.";
        _deleteSelection();
    }
}

void GraphicMap::SelectionDrawingTool::onKeyRelease(QKeyEvent* event)
{
    Q_UNUSED(event);
}

void GraphicMap::SelectionDrawingTool::_deleteSelection()
{
    const QPoint& topLeft(m_activeSelection.topLeft());
    const QPoint& bottomRight(m_activeSelection.bottomRight());
    for (int j = topLeft.y(); j < bottomRight.y(); j += 16)
    {
        for (int i = topLeft.x(); i < bottomRight.x(); i += 16)
        {
            m_mapGraphicScene.activeLayer()->setTile(quint16(i),
                                                     quint16(j),
                                                     -1,
                                                     -1);
        }
    }
}
