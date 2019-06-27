#pragma once

#include <QStandardItem>

namespace Misc {
class AbstractMapLevelTreeItem : public ::QStandardItem {
public:
    virtual void toggle() = 0;
};
}
