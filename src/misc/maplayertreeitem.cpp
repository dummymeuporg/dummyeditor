#include "editorlayer.hpp"

#include "misc/maplayertreeitem.hpp"

namespace Misc {
MapLayerTreeItem::MapLayerTreeItem(std::int8_t position, EditorLayer& layer)
    : m_editorLayer(layer), m_position(position)
{
    if (m_editorLayer.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

QVariant MapLayerTreeItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return QStringLiteral("Level %1").arg(m_position);
    }
    return QStandardItem::data(role);
}

void MapLayerTreeItem::toggle() {
    m_editorLayer.setVisible(!m_editorLayer.visible());
    if (m_editorLayer.visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

} // namespace Misc
