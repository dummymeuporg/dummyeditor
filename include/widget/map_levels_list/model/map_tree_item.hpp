#pragma once

#include <QStandardItem>

namespace Widget {
namespace MapLevelsList {
namespace Model {

class MapTreeItem : public QStandardItem {
public:
    MapTreeItem();
    virtual void toggle() = 0;
};

} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
