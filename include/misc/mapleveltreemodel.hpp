#pragma once

#include <memory>

#include <QStandardItemModel>
#include <QVariant>

class EditorMap;

namespace Misc {
class MapLevelTreeModel : public QStandardItemModel {
public:
    MapLevelTreeModel(std::shared_ptr<EditorMap>);
    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
    ) const override;
    /*
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    */
private:
    std::shared_ptr<EditorMap> m_editorMap;
};
} // namespace Misc
