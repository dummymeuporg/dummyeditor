#pragma once

#include <QStandardItem>

class EditorLevel;
class EditorMap;

namespace Misc {
class MapLevelTreeItem : public QStandardItem {
public:
    MapLevelTreeItem(EditorLevel&);
    QVariant data(int role = Qt::UserRole + 1) const override;
private:
    EditorLevel& m_editorLevel;
};
} // namespace Misc
