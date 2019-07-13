#include <QDebug>

#include "editor/map.hpp"
#include "editor/project.hpp"

#include "misc/mapdocument.hpp"

Misc::MapDocument::MapDocument(
    Editor::Project& project,
    const QString& name,
    std::shared_ptr<Editor::Map> map
)
    : m_editorProject(project),
      m_isModified(false),
      m_mapName(name),
      m_map(map)
{
    // XXX: build graphic layers
}


void Misc::MapDocument::save() {
    qDebug() << "Save " << m_mapName;
    m_map->save();
}
