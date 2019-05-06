#include <QDebug>
#include <QGraphicsItem>
#include <QPoint>

#include "dummy/map.h"
#include "misc/mapdocument.h"
#include "graphicmap/visiblegraphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/paintinggraphiclayerstate.h"
#include "graphicmap/selectiondrawingclipboard.h"

GraphicMap::PaintingGraphicLayerState::PaintingGraphicLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene,
                                   QPair<int, int>(16, 16))
{

}

GraphicMap::PaintingGraphicLayerState::~PaintingGraphicLayerState()
{

}


void
GraphicMap::PaintingGraphicLayerState::drawWithPen(const QPoint& point) const
{
    GraphicMap::VisibleGraphicLayer* layer =
        static_cast<VisibleGraphicLayer*>(m_mapGraphicsScene.activeLayer());
    std::shared_ptr<Dummy::Map> map(
        m_mapGraphicsScene.mapDocument()->map());

    const QRect& chipsetSelection = m_mapGraphicsScene.chipsetSelection();

    int width(chipsetSelection.width() / 16);
    int height(chipsetSelection.height() / 16);

    if (map != nullptr && width >= 0 && height >= 0)
    {
        for (int j = 0; j < height; ++j) {
            for(int i = 0; i < width; ++i) {
                layer->setTile(
                     quint16(point.x()
                             - (point.x() % 16)
                             + (i * 16)),
                     quint16(point.y()
                             - (point.y() % 16)
                             + (j * 16)),
                     qint16(chipsetSelection.x() + (i * 16)),
                     qint16(chipsetSelection.y() + (j * 16)));
            }
        }
    }
}

void
GraphicMap::PaintingGraphicLayerState::drawWithRectangle(
    const QPoint& point, const QRect& rectChipsetSelection) const
{
    GraphicMap::VisibleGraphicLayer* layer =
        static_cast<VisibleGraphicLayer*>(m_mapGraphicsScene.activeLayer());
    qint16 chipsetX = qint16(rectChipsetSelection.x()/16);
    qint16 chipsetY = qint16(rectChipsetSelection.y()/16);

    for (quint16 j = 0; j < rectChipsetSelection.height()/16; j++)
    {
        for (quint16 i = 0; i < rectChipsetSelection.width()/16; i++)
        {
            qDebug() << "CHIPSET: " << chipsetX + i << chipsetY + j;
            qDebug() << "TARGET: " << point.x() + i << point.y() + j;
            layer->setTile(
                quint16(point.x() + i * 16),
                quint16(point.y() + j * 16),
                (chipsetX + i) * 16, (chipsetY + j) * 16
            );
        }
    }
}

void
GraphicMap::PaintingGraphicLayerState::drawWithSelection(
    const QPoint& point,
    const SelectionDrawingClipboard& clipboard) const
{
    int clipboardIndex = 0;
    for(int j = 0;
        j < clipboard.selectionClipboard().height();
        j += 16)
    {
        for (int i = 0;
             i < clipboard.selectionClipboard().width();
             i += 16)
        {
            const std::tuple<qint16, qint16>& firstLayerTile(
                clipboard.firstLayerClipboard()[clipboardIndex]);
            const std::tuple<qint16, qint16>& secondLayerTile(
                clipboard.secondLayerClipboard()[clipboardIndex]);
            const std::tuple<qint16, qint16>& thirdLayerTile(
                clipboard.thirdLayerClipboard()[clipboardIndex]);

            qDebug() << std::get<0>(firstLayerTile) <<
                        std::get<1>(firstLayerTile);
            m_mapGraphicsScene.firstLayer()->setTile(
                quint16(point.x() + i),
                quint16(point.y() + j),
                std::get<0>(firstLayerTile) * 16,
                std::get<1>(firstLayerTile) * 16);

            m_mapGraphicsScene.secondLayer()->setTile(
                quint16(point.x() + i),
                quint16(point.y() + j),
                std::get<0>(secondLayerTile) * 16,
                std::get<1>(secondLayerTile) * 16);

            m_mapGraphicsScene.thirdLayer()->setTile(
                quint16(point.x() + i),
                quint16(point.y()  + j),
                std::get<0>(thirdLayerTile) * 16,
                std::get<1>(thirdLayerTile) * 16);

            ++clipboardIndex;

        }
    }

    m_mapGraphicsScene.adjustLayers();
}


void
GraphicMap::PaintingGraphicLayerState::drawCurrentSelection(
    const QPoint& point, QGraphicsItem* selectionItem) const
{
    qDebug() << "Draw current selection";
    if (nullptr != selectionItem) {
        qDebug() << "Point is " << point;

        selectionItem->setVisible(true);

        // Translate the coordinate to get the top upper corner of the tile.
        int x = point.x() - (point.x() % 16);
        int y = point.y() - (point.y() % 16);

        selectionItem->setPos(x, y);
    }
}
