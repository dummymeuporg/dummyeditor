#include "MapTools.hpp"
#include "ui_GeneralWindow.h"

#include "chipsetGraphicsScene.hpp"
#include "editor/layerBlocking.hpp"
#include "editor/layerGraphic.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "utils/definitions.hpp"

MapTools::MapTools(const ChipsetGraphicsScene& chipset, GraphicMap::MapGraphicsScene& map, Ui::GeneralWindow& ui)
    : m_chipsetScene(chipset)
    , m_mapScene(map)
    , m_toolsUI(ui)
{
    m_mapScene.linkToolSet(this);
}

void MapTools::clear()
{
    resetTools();
    resetLayerLink();
}

void MapTools::setActiveLayer(GraphicMap::VisibleGraphicLayer* layer)
{
    resetLayerLink();
    m_mapScene.clearSelectRect();

    // update grid
    m_uiLayerW   = layer->layer().width();
    m_uiLayerH   = layer->layer().height();
    m_uiGridStep = CELL_H;

    m_currLayerType = eLayerType::Visible;
    m_visLayer      = layer;

    updateGridDisplay();
}

void MapTools::setActiveLayer(GraphicMap::BlockingGraphicLayer* layer)
{
    resetLayerLink();
    m_mapScene.clearSelectRect();

    // update grid
    m_uiLayerW   = layer->layer().width();
    m_uiLayerH   = layer->layer().height();
    m_uiGridStep = BLOCK_H;

    m_currLayerType = eLayerType::Blocking;
    m_blockLayer    = layer;

    updateGridDisplay();
}

void MapTools::setActiveLayer(GraphicMap::EventGraphicLayer* layer)
{
    clear();

    m_currLayerType = eLayerType::Event;
    m_eventLayer    = layer;

    updateGridDisplay();
}

void MapTools::updateGridDisplay()
{
    if (m_toolsUI.actionToggleGrid->isChecked() && m_currLayerType != eLayerType::None)
        m_mapScene.drawGrid(m_uiLayerW, m_uiLayerH, m_uiGridStep);
    else
        m_mapScene.clearGrid();
}

void MapTools::resetTools()
{
    m_mapScene.setSelectRect(QRect());

    m_toolsUI.actionPen->setChecked(false);
    m_toolsUI.actionEraser->setChecked(false);
    m_toolsUI.actionSelection->setChecked(false);
    m_toolsUI.actionPaste->setChecked(false);

    m_toolsUI.actionCopy->setEnabled(false);
    m_toolsUI.actionCut->setEnabled(false);
}

void MapTools::resetLayerLink()
{
    m_currLayerType = eLayerType::None;
    m_visLayer      = nullptr;
    m_blockLayer    = nullptr;
    m_eventLayer    = nullptr;

    m_commandsHistory.clear();
    m_toolsUI.actionUndo->setEnabled(false);
    m_toolsUI.actionRedo->setEnabled(false);
    m_nbCommandsValid = 0;
}
void MapTools::setTool(eTools tool)
{
    resetTools();
    m_currMode = tool;

    switch (tool) {
    case eTools::Pen:
        m_toolsUI.actionPen->setChecked(true);
        break;
    case eTools::Eraser:
        m_toolsUI.actionEraser->setChecked(true);
        break;
    case eTools::Selection:
        m_toolsUI.actionSelection->setChecked(true);
        m_toolsUI.actionCopy->setEnabled(true);
        m_toolsUI.actionCut->setEnabled(true);
        break;
    case eTools::Paste:
        m_toolsUI.actionPaste->setChecked(true);
        break;
    default:
        break;
    }
}

QPoint MapTools::adjustOnGrid(const QPoint& pxCoords)
{
    int iStep = static_cast<int>(m_uiGridStep);
    if (iStep == 0)
        return pxCoords; // cannot do anything with % 0

    QPoint cellsCoords;
    cellsCoords.setX(pxCoords.x() - (pxCoords.x() % iStep));
    cellsCoords.setY(pxCoords.y() - (pxCoords.y() % iStep));

    return cellsCoords;
}

QRect MapTools::adjustOnGrid(const QRect& rawRect)
{
    int iStep = static_cast<int>(m_uiGridStep);

    QRect normalized = rawRect.normalized();
    QPoint p1        = adjustOnGrid(normalized.topLeft());
    QPoint p2        = adjustOnGrid(normalized.bottomRight());
    p2 += QPoint(iStep - 1, iStep - 1);

    forceInScene(p1);
    forceInScene(p2);

    return QRect(p1, p2);
}

void MapTools::forceInScene(QPoint& point)
{
    int maxX = static_cast<int>(m_uiLayerW * m_uiGridStep) - 1;
    int maxY = static_cast<int>(m_uiLayerH * m_uiGridStep) - 1;

    if (point.x() < 0)
        point.setX(0);
    if (point.x() > maxX)
        point.setX(maxX);

    if (point.y() < 0)
        point.setY(0);
    if (point.y() > maxY)
        point.setY(maxY);
}

QPixmap MapTools::previewVisible(const QRect& region)
{
    const QPixmap chipsetSelection = m_chipsetScene.selectionPixmap();
    if (chipsetSelection.isNull())
        return QPixmap();

    QPixmap previewImg(region.size());
    QPainter painter(&previewImg);
    const int rectW = region.width();
    const int rectH = region.height();
    const int dX    = static_cast<int>(chipsetSelection.width());
    const int dY    = static_cast<int>(chipsetSelection.height());

    for (int y = 0; y < rectH; y += dY) {
        for (int x = 0; x < rectW; x += dX) {
            painter.drawPixmap(QRect(x, y, dX, dY), chipsetSelection);
        }
    }

    return previewImg;
}

void MapTools::drawVisible(const QRect& region)
{
    if (m_currLayerType != eLayerType::Visible || m_visLayer == nullptr)
        return;

    const QRect& chipsetSelection = m_chipsetScene.selectionRect();
    if (chipsetSelection.isNull())
        return;

    tVisibleClipboard toDraw;
    toDraw.width  = static_cast<quint16>(region.width()) / CELL_W;
    toDraw.height = static_cast<quint16>(region.height()) / CELL_H;
    toDraw.content.resize(static_cast<size_t>(toDraw.width * toDraw.height));

    for (int x = 0; x < toDraw.width; ++x)
        for (int y = 0; y < toDraw.height; ++y) {
            int8_t newX = (chipsetSelection.x() / CELL_W) + (x % (chipsetSelection.width() / CELL_W));
            int8_t newY = (chipsetSelection.y() / CELL_H) + (y % (chipsetSelection.height() / CELL_H));

            toDraw.content[x + y * toDraw.width] = {newX, newY};
        }

    doCommand(std::make_unique<CommandPaint>(*this, region.topLeft(), std::move(toDraw)));
}

void MapTools::drawBlocking(const QRect& region)
{
    if (m_currLayerType != eLayerType::Blocking || m_blockLayer == nullptr)
        return;

    tBlockingClipboard toDraw;
    toDraw.width  = static_cast<quint16>(region.width()) / BLOCK_W;
    toDraw.height = static_cast<quint16>(region.height()) / BLOCK_H;
    toDraw.content.resize(static_cast<size_t>(toDraw.width * toDraw.height), true);
    doCommand(std::make_unique<CommandPaintBlocking>(*this, region.topLeft(), std::move(toDraw)));
}

void MapTools::eraseVisible(const QRect& region)
{
    if (m_currLayerType != eLayerType::Visible || m_visLayer == nullptr)
        return;

    tVisibleClipboard toErase;
    toErase.width  = static_cast<quint16>(region.width()) / CELL_W;
    toErase.height = static_cast<quint16>(region.height()) / CELL_H;
    toErase.content.resize(static_cast<size_t>(toErase.width * toErase.height), {-1, -1});

    doCommand(std::make_unique<CommandPaint>(*this, region.topLeft(), std::move(toErase)));
}

void MapTools::eraseBlocking(const QRect& region)
{
    if (m_currLayerType != eLayerType::Blocking || m_blockLayer == nullptr)
        return;

    tBlockingClipboard toErase;
    toErase.width  = static_cast<quint16>(region.width()) / BLOCK_W;
    toErase.height = static_cast<quint16>(region.height()) / BLOCK_H;
    toErase.content.resize(static_cast<size_t>(toErase.width * toErase.height), false);
    doCommand(std::make_unique<CommandPaintBlocking>(*this, region.topLeft(), std::move(toErase)));
}
void MapTools::copyCut(eCopyCut action)
{
    if (m_currLayerType != eLayerType::Visible || m_visLayer == nullptr)
        return;

    QRectF selectedRect = m_mapScene.selectionRect().toRect();

    std::vector<std::pair<int8_t, int8_t>> valuesInPatch;
    qint16 minX       = static_cast<quint16>(selectedRect.x()) / CELL_W;
    qint16 minY       = static_cast<quint16>(selectedRect.y()) / CELL_H;
    qint16 selectionW = static_cast<quint16>(selectedRect.width()) / CELL_W;
    qint16 selectionH = static_cast<quint16>(selectedRect.height()) / CELL_H;
    qint16 maxX       = minX + selectionW - 1;
    qint16 maxY       = minY + selectionH - 1;
    for (qint16 y = minY; y <= maxY; ++y)
        for (qint16 x = minX; x <= maxX; ++x) {
            size_t indexInLayer = y * m_visLayer->layer().width() + x;
            auto value          = m_visLayer->layer()[indexInLayer];
            valuesInPatch.push_back(value);
            if (action == eCopyCut::Cut) {
                m_visLayer->setTile(x, y, {-1, -1});
            }
        }
    m_visibleClipboard.width   = selectionW;
    m_visibleClipboard.height  = selectionH;
    m_visibleClipboard.content = valuesInPatch;
}

void MapTools::paste(const QPoint& point)
{
    if (m_visibleClipboard.width == 0 || m_visibleClipboard.height == 0)
        return;

    if (m_currLayerType != eLayerType::Visible || m_visLayer == nullptr)
        return;

    doCommand(std::make_unique<CommandPaint>(*this, QPoint(point), tVisibleClipboard(m_visibleClipboard)));
}

void MapTools::previewTool(const QRect& clickingRegion)
{
    QRect adjustedRegion = adjustOnGrid(clickingRegion);
    QPixmap previewImg;

    switch (m_currMode) {
    case eTools::Pen:

        if (m_currLayerType == eLayerType::Visible) {
            previewImg = previewVisible(adjustedRegion);
        } else if (m_currLayerType == eLayerType::Blocking) {
            previewImg = QPixmap(adjustedRegion.size());
            previewImg.fill(QColor(255, 0, 0, 50));
        }

        m_mapScene.setPreview(previewImg, adjustedRegion.topLeft());
        break;

    case eTools::Eraser:
        m_mapScene.setSelectRect(adjustedRegion); // show a preview with selection rect
        break;

    case eTools::Selection:
        m_mapScene.setSelectRect(adjustedRegion);
        break;

    case eTools::Paste:
    default:
        break;
    }
}

void MapTools::useTool(const QRect& clickingRegion)
{
    QRect adjustedRegion = adjustOnGrid(clickingRegion);

    switch (m_currMode) {
    case eTools::Pen:
        // Hide preview
        m_mapScene.clearPreview();
        // and actually erase
        if (m_currLayerType == eLayerType::Visible)
            drawVisible(adjustedRegion);
        else if (m_currLayerType == eLayerType::Blocking)
            drawBlocking(adjustedRegion);

        break;

    case eTools::Eraser:
        // Hide preview
        m_mapScene.setSelectRect(QRect());
        // and actually erase
        if (m_currLayerType == eLayerType::Visible)
            eraseVisible(adjustedRegion);
        else if (m_currLayerType == eLayerType::Blocking)
            eraseBlocking(adjustedRegion);

        break;

    case eTools::Selection:
        m_mapScene.setSelectRect(adjustedRegion);
        break;

    case eTools::Paste:
        paste(adjustOnGrid(clickingRegion.bottomRight()));
        break;

    default:
        break;
    }
}


// Commands history

void MapTools::doCommand(std::unique_ptr<Command>&& c)
{
    c->execute();

    // Here we don't consider overflow of a max of commands to remember because the commands history is reset each time
    // the active layer is changed.
    auto& histo = m_commandsHistory; // alias

    if (m_nbCommandsValid < histo.size())
        histo.erase(histo.begin() + static_cast<long>(m_nbCommandsValid), histo.end());

    histo.push_back(std::move(c));
    ++m_nbCommandsValid;

    // update UI
    m_toolsUI.actionUndo->setEnabled(true);
    m_toolsUI.actionRedo->setEnabled(false);
}

void MapTools::undo()
{
    if (m_nbCommandsValid == 0)
        return;

    m_commandsHistory[m_nbCommandsValid - 1]->undo();
    --m_nbCommandsValid;

    // update UI
    m_toolsUI.actionUndo->setEnabled(m_nbCommandsValid > 0);
    m_toolsUI.actionRedo->setEnabled(true);
}

void MapTools::redo()
{
    if (m_nbCommandsValid >= m_commandsHistory.size())
        return;

    ++m_nbCommandsValid;
    m_commandsHistory[m_nbCommandsValid - 1]->execute();

    // update UI
    m_toolsUI.actionUndo->setEnabled(true);
    m_toolsUI.actionRedo->setEnabled(m_nbCommandsValid < m_commandsHistory.size());
}

MapTools::CommandPaint::CommandPaint(MapTools& parent, QPoint&& pxCoord, tVisibleClipboard&& clip)
    : m_parent(parent)
    , m_position(pxCoord)
    , m_toDraw(clip)
{}

void MapTools::CommandPaint::execute()
{
    m_replacedTiles = m_toDraw;

    if (m_parent.m_currLayerType != eLayerType::Visible || m_parent.m_visLayer == nullptr)
        return;

    int minX = m_position.x() / CELL_W;
    int minY = m_position.y() / CELL_H;
    for (int y = minY; y < (m_toDraw.height + minY) && y < m_parent.m_uiLayerH; ++y) {
        for (int x = minX; x < (m_toDraw.width + minX) && x < m_parent.m_uiLayerW; ++x) {
            size_t idxInClipboard                   = static_cast<size_t>((y - minY) * m_toDraw.width + (x - minX));
            m_replacedTiles.content[idxInClipboard] = m_parent.m_visLayer->tile(x, y);

            auto newValue = m_toDraw.content[idxInClipboard];
            m_parent.m_visLayer->setTile(static_cast<quint16>(x), static_cast<quint16>(y), newValue);
        }
    }
}

void MapTools::CommandPaint::undo()
{
    if (m_parent.m_currLayerType != eLayerType::Visible || m_parent.m_visLayer == nullptr)
        return;

    int minX = m_position.x() / CELL_W;
    int minY = m_position.y() / CELL_H;
    for (int y = minY; y < (m_toDraw.height + minY) && y < m_parent.m_uiLayerH; ++y) {
        for (int x = minX; x < (m_toDraw.width + minX) && x < m_parent.m_uiLayerW; ++x) {
            size_t idxInClipboard = static_cast<size_t>((y - minY) * m_toDraw.width + (x - minX));
            auto newValue         = m_replacedTiles.content[idxInClipboard];
            m_parent.m_visLayer->setTile(static_cast<quint16>(x), static_cast<quint16>(y), newValue);
        }
    }
}

MapTools::CommandPaintBlocking::CommandPaintBlocking(MapTools& parent, QPoint&& pxCoord, tBlockingClipboard&& clip)
    : m_parent(parent)
    , m_position(pxCoord)
    , m_toDraw(clip)
{}

void MapTools::CommandPaintBlocking::execute()
{
    m_replacedTiles = m_toDraw;

    if (m_parent.m_currLayerType != eLayerType::Blocking || m_parent.m_blockLayer == nullptr)
        return;

    int minX = m_position.x() / BLOCK_W;
    int minY = m_position.y() / BLOCK_H;
    for (int y = minY; y < (m_toDraw.height + minY) && y < m_parent.m_uiLayerH; ++y) {
        for (int x = minX; x < (m_toDraw.width + minX) && x < m_parent.m_uiLayerW; ++x) {
            size_t idxInClipboard                   = static_cast<size_t>((y - minY) * m_toDraw.width + (x - minX));
            m_replacedTiles.content[idxInClipboard] = m_parent.m_blockLayer->tile(x, y);

            auto newValue = m_toDraw.content[idxInClipboard];
            m_parent.m_blockLayer->setTile(static_cast<quint16>(x), static_cast<quint16>(y), newValue);
        }
    }
}

void MapTools::CommandPaintBlocking::undo()
{
    if (m_parent.m_currLayerType != eLayerType::Blocking || m_parent.m_blockLayer == nullptr)
        return;

    int minX = m_position.x() / BLOCK_W;
    int minY = m_position.y() / BLOCK_H;
    for (int y = minY; y < (m_toDraw.height + minY) && y < m_parent.m_uiLayerH; ++y) {
        for (int x = minX; x < (m_toDraw.width + minX) && x < m_parent.m_uiLayerW; ++x) {
            size_t idxInClipboard = static_cast<size_t>((y - minY) * m_toDraw.width + (x - minX));
            auto newValue         = m_replacedTiles.content[idxInClipboard];
            m_parent.m_blockLayer->setTile(static_cast<quint16>(x), static_cast<quint16>(y), newValue);
        }
    }
}
