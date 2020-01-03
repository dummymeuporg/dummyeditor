#ifndef MAPTREEITEM_H
#define MAPTREEITEM_H

#include <QStandardItem>

namespace Widget {
namespace MapFloorsList {
namespace Model {

//////////////////////////////////////////////////////////////////////////////
//  MapTreeItem class
//////////////////////////////////////////////////////////////////////////////

class MapTreeItem : public QStandardItem {
public:
    virtual void toggle() = 0;
    virtual void setVisible(bool) = 0;
    virtual void setSelected() = 0;
};

} // namespace Model
} // namespace MapFloorsList
} // namespace Widget

#endif // MAPTREEITEM_H
