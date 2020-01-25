#ifndef DRAWINGTOOLBARWIDGET_H
#define DRAWINGTOOLBARWIDGET_H

#include <QToolBar>
#include <memory>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class ChipsetGraphicsScene;
class QActionGroup;

namespace GraphicMap {
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTools

//////////////////////////////////////////////////////////////////////////////
//  DrawingToolbarWidget class
//////////////////////////////////////////////////////////////////////////////

class DrawingToolBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingToolBarWidget(QWidget* parent = nullptr);

    void clear();
    void changeActiveLayer(GraphicMap::MapGraphicsScene*,
                           const ChipsetGraphicsScene* chipset,
                           std::vector<DrawingTools::DrawingTool*>&);

private:
    QToolBar* m_toolbar = nullptr;
    std::unique_ptr<QActionGroup> m_actionGrp;
    std::vector<std::unique_ptr<QAction>> m_actions;
};

#endif // DRAWINGTOOLBARWIDGET_H
