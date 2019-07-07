#pragma once

#include <QAction>

namespace DrawingTool {
class DrawingTool;
} // namespace DrawingTool

namespace Widget {
namespace DrawingToolbar {

class DrawingToolAction : public ::QAction {
    Q_OBJECT
public:
    DrawingToolAction(DrawingTool::DrawingTool*, QWidget* parent = nullptr);
    DrawingTool::DrawingTool* drawingTool() const {
        return m_drawingTool;
    }
signals:
    void trigerred(DrawingTool::DrawingTool*);
public slots:
    void setDrawingTool(bool);
private:
    DrawingTool::DrawingTool* m_drawingTool;
};

} // namespace DrawingToolbar
} // namespace Widget
