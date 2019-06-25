#include <algorithm>
#include "editormap.hpp"
#include "misc/mapleveltreemodel.hpp"

namespace Misc {
MapLevelTreeModel::MapLevelTreeModel(std::shared_ptr<EditorMap> editorMap)
    : m_editorMap(editorMap)
{
    // XXX: setup hierarchy.
    QList<QStandardItem*> headers;
    headers.append(new QStandardItem("Levels"));
    appendColumn(headers);
    for (int i = m_editorMap->levelsCount() - 1; i >= 0; --i) {
        QList<QStandardItem *> levelItem { new QStandardItem("Level") };
        const Dummy::Core::MapLevel& mapLevel(m_editorMap->mapLevels()[i]);
        for (auto it = mapLevel.layers().rbegin();
             it != mapLevel.layers().rend();
             ++it)
        {
            QList<QStandardItem *> layerItem {
                new QStandardItem(QStringLiteral("Layer %1").arg(it->first))
            };
            levelItem.first()->appendRow(layerItem);
        }
        appendRow(levelItem);
    }
}

QVariant MapLevelTreeModel::headerData(
    int section,
    Qt::Orientation orientation,
    int role
) const {
    return QVariant();
}

} // namespace Misc
