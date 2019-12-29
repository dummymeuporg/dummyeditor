#pragma once

#include <QAction>

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTool

namespace Widget {
namespace DrawingToolbar {

class DrawingToolAction : public ::QAction {
    Q_OBJECT
public:
    DrawingToolAction(DrawingTools::DrawingTool*, QWidget* parent = nullptr);
    DrawingTools::DrawingTool& drawingTool() const {
        return *m_drawingTool;
    }
signals:
    void trigerred(DrawingTools::DrawingTool*);
public slots:
    void setDrawingTool(bool);
private:
    DrawingTools::DrawingTool* m_drawingTool;
};

} // namespace DrawingToolbar
} // namespace Widget
