#pragma once

#include <QtGlobal>
#include <QVector>

#include "drawing_tool/blocking/pen.hpp"
#include "drawing_tool/blocking/eraser.hpp"

#include "graphicmap/graphiclayer.hpp"

namespace Editor {
class BlockingLayer;
} // namespace Editor

namespace GraphicMap {
class BlockingSquareItem;
class MapGraphicsScene;
class MapSceneLayer;
class BlockingGraphicLayer : public GraphicLayer
{
public:
    BlockingGraphicLayer(
        Editor::BlockingLayer&,
        MapGraphicsScene&,
        int zValue
    );
    ~BlockingGraphicLayer() override;
    MapSceneLayer& removeTile(quint16, quint16) override;
    void toggleTile(quint16, quint16);
    void setTile(quint16, quint16, bool);
    Editor::Layer& editorLayer() override;

    inline const Editor::BlockingLayer& layer() const {
        return m_blockingLayer;
    }

    std::vector<DrawingTool::DrawingTool*> drawingTools() override;
    void accept(GraphicLayerVisitor&) override;

    std::shared_ptr<LayerClipboard::Clipboard>
    getClipboardRegion(const QRect& clip) override;
private:
    void _draw(int, quint16, quint16);
    Editor::BlockingLayer& m_blockingLayer;
    QVector<BlockingSquareItem*> m_crossItems;

    // Drawing tools
    /*
    DrawingTool::Blocking::Pen m_pen;
    DrawingTool::Blocking::Eraser m_eraser;
    */
};
} // namespace GraphicMap
