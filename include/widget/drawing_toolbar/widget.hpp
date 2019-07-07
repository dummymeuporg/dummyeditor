#pragma once

#include <QWidget>

class QToolBar;
class QActionGroup;

namespace DrawingTool {
class DrawingTool;
} // namespace DrawingTool

namespace Widget {
namespace DrawingToolbar {

class Widget : public ::QWidget {
    Q_OBJECT
    Widget(::QWidget* parent = nullptr);
    void reset(const std::vector<DrawingTool::DrawingTool*>&);
private:
    ::QToolBar* m_toolbar;
    ::QActionGroup* m_actionGroup;
};

} // namespace DrawingToolbar
} // namespace Widget
