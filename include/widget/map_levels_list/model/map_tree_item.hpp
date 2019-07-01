#pragma once

#include <QStandardItem>

namespace Widget {
namespace MapLevelsList {
namespace Model {

class MapTreeItem : public QStandardItem {
public:
    virtual void toggle() = 0;
    virtual void setVisible(bool) = 0;
};

} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
