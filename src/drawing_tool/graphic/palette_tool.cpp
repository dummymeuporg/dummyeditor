#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "chipsetgraphicsscene.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "drawing_tool/graphic/palette_tool.hpp"
#include "drawing_tool/visitor.hpp"


namespace DrawingTool {
namespace Graphic {

PaletteTool::PaletteTool(
        QIcon&& icon,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicTool(std::move(icon), mapGraphicsScene, visibleGraphicLayer),
      m_chipsetGraphicsScene(nullptr),
      m_selectionRectItem(nullptr),
      m_selectionItem(nullptr),
      m_isSelecting(false)
{}

void PaletteTool::emitDrawingToolSelected() {
    GraphicTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void
PaletteTool::paletteMousePressEvent(::QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr != m_chipsetGraphicsScene
            && mouseEvent->buttons() & Qt::LeftButton && !m_isSelecting)
    {
        m_isSelecting = true;
        m_selectionStart = mouseEvent->scenePos().toPoint();

        if (m_selectionStart.x() < m_chipsetGraphicsScene->width()
            && m_selectionStart.y() < m_chipsetGraphicsScene->height())
        {
            if (m_selectionRectItem != nullptr) {
                m_chipsetGraphicsScene->invalidate(
                    m_selectionRectItem->rect()
                );
                m_chipsetGraphicsScene->removeItem(
                    m_selectionRectItem
                );
            }

            // Add a square
            QBrush brush(QColor(66, 135, 245));
            int x = m_selectionStart.x() - (m_selectionStart.x() % 16);
            int y = m_selectionStart.y() - (m_selectionStart.y() % 16);
            setSelection(
                QRect(x, y, 16, 16),
                m_chipsetGraphicsScene->chipset()->pixmap()
            );
            m_selectionRectItem = m_chipsetGraphicsScene->addRect(
                m_rectSelection
            );
            m_selectionRectItem->setBrush(brush);
            m_selectionRectItem->setOpacity(0.5);
        }
    }
}

void
PaletteTool::paletteMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr != m_selectionRectItem && m_isSelecting) {
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
        m_selectionRectItem = m_chipsetGraphicsScene->addRect(
            m_rectSelection
        );
        m_selectionRectItem->setBrush(brush);
        m_selectionRectItem->setOpacity(0.5);

    }
}

void
PaletteTool::paletteMouseReleaseEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr != m_selectionItem) {
        m_isSelecting = false;
    }
}

void
PaletteTool::setSelection(
    const QRect& selection,
    const QPixmap& chipsetPixmap
) {
    m_rectSelection = selection;
    m_selectionPixmap = chipsetPixmap.copy(selection);
    m_selectionItem = new ::QGraphicsPixmapItem(m_selectionPixmap);
}

void
PaletteTool::setChipsetGraphicsScene(
    ::ChipsetGraphicsScene* chipsetGraphicsScene
) {
    m_chipsetGraphicsScene = chipsetGraphicsScene;
}

void PaletteTool::onUnselected() {
    if (nullptr != m_chipsetGraphicsScene) {
        m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
        m_selectionItem = nullptr;
    }
}

void PaletteTool::onSelected() {
}

} // namespace Graphic
} // namespace DrawingTool
