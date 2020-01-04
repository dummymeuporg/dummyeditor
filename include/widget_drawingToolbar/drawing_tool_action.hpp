#ifndef DRAWINGTOOLACTION_H
#define DRAWINGTOOLACTION_H

#include <QAction>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTools

namespace DrawingToolbar {

//////////////////////////////////////////////////////////////////////////////
//  DrawingToolAction class
//////////////////////////////////////////////////////////////////////////////

class DrawingToolAction : public QAction
{
    Q_OBJECT
public:
    DrawingToolAction(DrawingTools::DrawingTool*, QWidget* parent = nullptr);

    DrawingTools::DrawingTool& drawingTool() const { return *m_drawingTool; }

signals:
    void trigerred(DrawingTools::DrawingTool*);

public slots:
    void setDrawingTool(bool);

private:
    DrawingTools::DrawingTool* m_drawingTool;
};

} // namespace DrawingToolbar

#endif // DRAWINGTOOLACTION_H
