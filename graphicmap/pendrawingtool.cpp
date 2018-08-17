#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

#include "dummy/map.h"
#include "dummy/project.h"
#include "misc/mapdocument.h"

#include "graphicmap/visiblegraphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/paintinglayerstate.h"
#include "graphicmap/pendrawingtool.h"

GraphicMap::PenDrawingTool::PenDrawingTool(
    GraphicMap::MapGraphicsScene& mapGraphicScene)
    : DrawingTool(mapGraphicScene), m_selectionItem(nullptr)
{

}

GraphicMap::PenDrawingTool::~PenDrawingTool() {

}

void
GraphicMap::PenDrawingTool::onMousePress(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_mapGraphicScene.mapDocument() == nullptr) {
        return;
    }

    if (mouseEvent->buttons() & Qt::LeftButton) {
        m_isDrawing = true;
        _setTiles(mouseEvent->scenePos().toPoint());
    }
}

void GraphicMap::PenDrawingTool::chipsetSelectionChanged(
    const QRect& selection)
{
    if (selection.size() == QSize(0, 0))
    {
        if (nullptr != m_selectionItem)
        {
            m_mapGraphicScene.removeItem(m_selectionItem);
            m_selectionItem = nullptr;
        }
        return;
    }
    std::shared_ptr<Dummy::Map> map(
        m_mapGraphicScene.mapDocument()->map());

    // XXX: Ugly
    QPixmap chipsetPixmap(
        m_mapGraphicScene.mapDocument()->project()->fullpath() + "/chipsets/" +
        map->chipset());

    m_selectionItem = new QGraphicsPixmapItem(
        chipsetPixmap.copy(selection));
    m_selectionItem->setVisible(false);
    m_selectionItem->setZValue(100);
    m_mapGraphicScene.addItem(m_selectionItem);

    qDebug() << "SELECTION CHANGED" << selection;
}

void GraphicMap::PenDrawingTool::_setTiles(const QPoint& originPoint)
{
    m_mapGraphicScene.paintingLayerState().drawWithPen(originPoint);
}

void
GraphicMap::PenDrawingTool::onMouseMove(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    qDebug() << "On mouse move Pen";
    if (mouseEvent->buttons() & Qt::LeftButton) {
        if (m_isDrawing) {
             m_mapGraphicScene.paintingLayerState().drawWithPen(
                mouseEvent->scenePos().toPoint());
        }
    }
    m_mapGraphicScene.paintingLayerState().drawCurrentSelection(
       mouseEvent->scenePos().toPoint(), m_selectionItem);
}

void
GraphicMap::PenDrawingTool::onMouseRelease(
    QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    m_isDrawing = false;
}

void GraphicMap::PenDrawingTool::onMouseLeave()
{
    if (m_selectionItem != nullptr) {
        m_selectionItem->setVisible(false);
    }
}


void GraphicMap::PenDrawingTool::onKeyPress(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Control)
    {
        qDebug() << "Ctrl pressed!";
    }
}

void GraphicMap::PenDrawingTool::onKeyRelease(QKeyEvent* event)
{
    Q_UNUSED(event);
}
