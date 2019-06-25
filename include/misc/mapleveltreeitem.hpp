#pragma once

#include <QStandardItem>

namespace Misc {
class MapLevelTreeItem : public QStandardItem {
public:
    MapLevelTreeItem(const QString&, bool = true);
    bool checked() const {
        return m_checked;
    }
    void setChecked(bool);
    const QString& content() const {
        return m_content;
    }
private:
    QString m_content;
    bool m_checked;
};
} // namespace Misc
