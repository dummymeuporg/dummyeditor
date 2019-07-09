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
        GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : GraphicTool(std::move(icon), visibleGraphicLayer),
      m_chipsetGraphicsScene(nullptr),
      m_selectionRectItem(nullptr),
      m_chipset(nullptr),
      m_isSelecting(false)
{}

void PaletteTool::setChipsetSelection(QRect rect) {
    m_selection = rect;
}

void PaletteTool::emitDrawingToolSelected() {
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void
PaletteTool::paletteMousePressEvent(::QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr != m_chipset && mouseEvent->buttons() & Qt::LeftButton) {
        m_isSelecting = true;
        m_selectionStart = mouseEvent->scenePos().toPoint();

        if (m_selectionStart.x() < m_chipset->boundingRect().width()
            && m_selectionStart.y() < m_chipset->boundingRect().height())
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
            QPen pen(Qt::red, 2);
            int x = m_selectionStart.x() - (m_selectionStart.x() % 16);
            int y = m_selectionStart.y() - (m_selectionStart.y() % 16);
            //setSelection(QRect(x, y, 16, 16));
            m_selectionRectItem = m_chipsetGraphicsScene->addRect(
                m_currentSelection, pen
            );
        }
    }
}

void
PaletteTool::paletteMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr != m_chipset && m_isSelecting) {
        QPoint pt = mouseEvent->scenePos().toPoint();

        pt.setX(std::min(pt.x(), m_chipset->pixmap().width() - 16));
        pt.setY(std::min(pt.y(), m_chipset->pixmap().height() - 16));

        if (m_selectionRectItem != nullptr) {
            m_chipsetGraphicsScene->removeItem(m_selectionRectItem);
            m_selectionRectItem = nullptr;
        }

        QPen pen(Qt::red, 2);

        int x = m_selectionStart.x() - (m_selectionStart.x() % 16);
        int y = m_selectionStart.y() - (m_selectionStart.y() % 16);
        int xEnd = pt.x() + (16 - (pt.x() % 16));
        int yEnd = pt.y() + (16 - (pt.y() % 16));

        if (pt.x() >= m_selectionStart.x()
            && pt.y() >= m_selectionStart.y())
        {
            m_chipsetGraphicsScene->setSelection(
                QRect(x, y, xEnd - x, yEnd - y)
            );
            m_selectionRectItem = m_chipsetGraphicsScene->addRect(
                m_currentSelection, pen
            );
        }
    }
}

void
PaletteTool::paletteMouseReleaseEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr != m_chipset) {
        m_isSelecting = false;
    }
}

void
PaletteTool::setSelection(
    const QRect& selection,
    const QPixmap& selectionPixmap
) {
    m_selection = selection;
    m_selectionPixmap = selectionPixmap;
    m_chipset = new ::QGraphicsPixmapItem(m_selectionPixmap);
}

void
PaletteTool::setChipsetGraphicsScene(
    ::ChipsetGraphicsScene* chipsetGraphicsScene
) {
    m_chipsetGraphicsScene = chipsetGraphicsScene;
}

} // namespace Graphic
} // namespace DrawingTool
