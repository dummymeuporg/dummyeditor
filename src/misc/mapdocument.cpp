#include <QDebug>

#include "core/graphic_map.hpp"

#include "editorproject.hpp"

#include "misc/mapdocument.hpp"

Misc::MapDocument::MapDocument(
    EditorProject& project,
    const QString& name,
    std::shared_ptr<Dummy::Core::GraphicMap> map
)
    : m_editorProject(project),
      m_isModified(false),
      m_mapName(name),
      m_map(map)
{
}


void Misc::MapDocument::save() {
    qDebug() << "Save " << m_mapName;
    //m_map->save();
}
