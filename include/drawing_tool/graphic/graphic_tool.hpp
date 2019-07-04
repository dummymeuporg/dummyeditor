#pragma once

#include <QRect>
#include "drawing_tool/drawing_tool.hpp"

namespace GraphicMap {
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace DrawingTool {

namespace Graphic {

class GraphicTool : public DrawingTool {
public:
    GraphicTool(GraphicMap::VisibleGraphicLayer&);
public slots:
    void setChipsetSelection(QRect);
private:
    GraphicMap::VisibleGraphicLayer& m_visibleGraphicLayer;
    QRect m_chipsetSelection;
};


} // namespace Graphic

} // namespace DrawingTool
