#include <QDebug>

#include "editor/map.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/selectiondrawingtool.hpp"
#include "graphicmap/selectiondrawingclipboard.hpp"

GraphicMap::SelectionDrawingClipboard::SelectionDrawingClipboard(
    GraphicMap::SelectionDrawingTool& selectionDrawingTool) :
    m_selectionDrawingTool(selectionDrawingTool),
    m_selectionClipboard(m_selectionDrawingTool.activeSelection())
{

    const QRect& activeSelection(m_selectionDrawingTool.activeSelection());
    const std::shared_ptr<Editor::Map> map(
        m_selectionDrawingTool.mapGraphicsScene().map());
    int width = activeSelection.width() / 16;
    int height = activeSelection.height() / 16;
    int newSize(width * height);

    m_firstLayerClipboard.resize(newSize);
    m_secondLayerClipboard.resize(newSize);
    m_thirdLayerClipboard.resize(newSize);
    m_blockingLayerClipboard.resize(newSize);
    qDebug() << "Active selection: " << activeSelection;

    int clipboardIndex = 0;
    for (int j = 0; j < activeSelection.height(); j += 16)
    {
        for (int i = 0; i < activeSelection.width(); i += 16)
        {
            quint16 coordX = quint16((activeSelection.x() + i) / 16),
                    coordY = quint16((activeSelection.y() + j) / 16);
            quint16 index(coordY * map->width() + coordX);
            qDebug() << "Copy " << index;
            m_firstLayerClipboard[clipboardIndex] = map->firstLayer()[index];
            m_secondLayerClipboard[clipboardIndex] = map->secondLayer()[index];
            m_thirdLayerClipboard[clipboardIndex] = map->thirdLayer()[index];
            m_blockingLayerClipboard[clipboardIndex] =
                map->blockingLayer()[index];
            ++clipboardIndex;
        }
    }
}
