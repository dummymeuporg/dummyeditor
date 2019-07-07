#include <QActionGroup>
#include <QToolBar>
#include <QHBoxLayout>

#include "drawing_tool/drawing_tool.hpp"

#include "widget/drawing_toolbar/widget.hpp"

namespace Widget {
namespace DrawingToolbar {

Widget::Widget(::QWidget* parent) :
    QWidget(parent),
    m_toolbar(new QToolBar(this)),
    m_actionGroup(new QActionGroup(m_toolbar))
{
    // Set empty toolbar for the moment.
    setLayout(new QHBoxLayout());
    layout()->addWidget(m_toolbar);
}

void
Widget::reset(const std::vector<DrawingTool::DrawingTool*>& drawingTools) {
    layout()->removeWidget(m_toolbar);
    delete m_toolbar;
    delete m_actionGroup;

    m_toolbar = new QToolBar(this);
    m_actionGroup = new QActionGroup(m_toolbar);

    for (auto& tool: drawingTools) {
        auto action(new QAction(m_actionGroup));
        action->setIcon(tool->icon());
        action->setText(tr("Tool"));
        action->setCheckable(true);
        m_actionGroup->addAction(action);
    }
    m_toolbar->addActions(m_actionGroup->actions());
}

} // namespace DrawingToolbar
} // namespace Widget
