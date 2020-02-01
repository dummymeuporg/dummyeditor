#ifndef MAPTOOLS_H
#define MAPTOOLS_H

#include <QPixmap>
#include <QRect>
#include <cstdint>
#include <memory>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Ui {
class GeneralWindow;
}

namespace GraphicMap {
class MapGraphicsScene;
class EventGraphicLayer;
class VisibleGraphicLayer;
class BlockingGraphicLayer;
} // namespace GraphicMap

class ChipsetGraphicsScene;

//////////////////////////////////////////////////////////////////////////////
//  MapTools class
//////////////////////////////////////////////////////////////////////////////

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo()    = 0;
};

class MapTools
{
    friend class Command;

public:
    enum class eTools
    {
        Pen,
        Eraser,
        Selection,
        Paste,
    };
    enum class eCopyCut
    {
        Copy,
        Cut,
    };

    explicit MapTools(const ChipsetGraphicsScene&, GraphicMap::MapGraphicsScene&, Ui::GeneralWindow&);

    void clear();

    void setActiveLayer(GraphicMap::VisibleGraphicLayer*);
    void setActiveLayer(GraphicMap::BlockingGraphicLayer*);
    void setActiveLayer(GraphicMap::EventGraphicLayer*);

    void setTool(eTools tool);

    void setGrid(bool gridVisible = true);
    void updateGridDisplay();

    void previewTool(const QRect& clickingRegion);
    void useTool(const QRect& clickingRegion);

    void copyCut(eCopyCut);

    void undo();
    void redo();

private:
    void resetTools();
    void resetLayerLink();

    QPoint adjustOnGrid(const QPoint& pxCoords);
    QRect adjustOnGrid(const QRect& rawRect);
    void forceInScene(QPoint& point); // set the point in the scene if it's out

    QPixmap previewVisible(const QRect&);

    void drawBlocking(const QRect&);
    void drawVisible(const QRect&);

    void eraseBlocking(const QRect&);
    void eraseVisible(const QRect&);

    void paste(const QPoint&);

    void doCommand(std::unique_ptr<Command>&& c);


    enum class eLayerType
    {
        None,
        Visible,
        Blocking,
        Event,
    };

    struct tVisibleClipboard
    {
        int16_t width  = 0;
        int16_t height = 0;
        std::vector<std::pair<int8_t, int8_t>> content;
    };

    struct tBlockingClipboard
    {
        int16_t width  = 0;
        int16_t height = 0;
        std::vector<bool> content;
    };

    const ChipsetGraphicsScene& m_chipsetScene;
    GraphicMap::MapGraphicsScene& m_mapScene;
    Ui::GeneralWindow& m_toolsUI;

    std::vector<std::unique_ptr<Command>> m_commandsHistory; // is reset each time we change the active layer
    size_t m_nbCommandsValid = 0;

    eTools m_currMode                              = eTools::Selection;
    eLayerType m_currLayerType                     = eLayerType::None;
    GraphicMap::VisibleGraphicLayer* m_visLayer    = nullptr;
    GraphicMap::BlockingGraphicLayer* m_blockLayer = nullptr;
    GraphicMap::EventGraphicLayer* m_eventLayer    = nullptr;
    tVisibleClipboard m_visibleClipboard;
    tBlockingClipboard m_blockingClipboard; // unused yet

    uint16_t m_uiLayerW   = 0;
    uint16_t m_uiLayerH   = 0;
    uint32_t m_uiGridStep = 0;

    //////////////
    // Command history

    class CommandPaint : public Command
    {
    public:
        CommandPaint(MapTools& parent, QPoint&& pxCoord, tVisibleClipboard&& clip);
        void execute() override;
        void undo() override;

    private:
        MapTools& m_parent;
        QPoint m_position;
        tVisibleClipboard m_toDraw;
        tVisibleClipboard m_replacedTiles;
    };
    class CommandPaintBlocking : public Command
    {
    public:
        CommandPaintBlocking(MapTools& parent, QPoint&& pxCoord, tBlockingClipboard&& clip);
        void execute() override;
        void undo() override;

    private:
        MapTools& m_parent;
        QPoint m_position;
        tBlockingClipboard m_toDraw;
        tBlockingClipboard m_replacedTiles;
    };
};


#endif // MAPTOOLS_H
