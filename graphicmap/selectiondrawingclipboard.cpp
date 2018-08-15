#include <QDebug>

#include "dummy/map.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/selectiondrawingtool.h"
#include "graphicmap/selectiondrawingclipboard.h"

GraphicMap::SelectionDrawingClipboard::SelectionDrawingClipboard(
    GraphicMap::SelectionDrawingTool& selectionDrawingTool) :
    m_selectionDrawingTool(selectionDrawingTool),
    m_selectionClipboard(m_selectionDrawingTool.activeSelection())
{

    const QRect& activeSelection(m_selectionDrawingTool.activeSelection());
    const std::shared_ptr<Dummy::Map> map(
        m_selectionDrawingTool.mapGraphicsScene().map());
    int width = activeSelection.width() / 16;
    int height = activeSelection.height() / 16;
    int newSize(width * height);

    m_firstLayerClipboard.resize(newSize);
    m_secondLayerClipboard.resize(newSize);
    m_thirdLayerClipboard.resize(newSize);
    qDebug() << "Active selection: " << activeSelection;

    int clipboardIndex = 0;
    for (int j = 0; j < activeSelection.height(); j += 16)
    {
        for (int i = 0; i < activeSelection.width(); i += 16)
        {
            quint16 coordX((activeSelection.x() + i) / 16),
                    coordY((activeSelection.y() + j) / 16);
            quint16 index(coordY * map->width() + coordX);
            qDebug() << "Copy " << index;
            m_firstLayerClipboard[clipboardIndex] = map->firstLayer()[index];
            m_secondLayerClipboard[clipboardIndex] = map->secondLayer()[index];
            m_thirdLayerClipboard[clipboardIndex] = map->thirdLayer()[index];

            ++clipboardIndex;
        }
    }
}
