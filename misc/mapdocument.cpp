#include <QDebug>

#include "dummy/project.h"

#include "mapdocument.h"

Misc::MapDocument::MapDocument(Dummy::Project& project,
                               std::shared_ptr<Dummy::Map> map)
    : m_project(project), m_isModified(false), m_map(map)
{
}


void Misc::MapDocument::save() {
    qDebug() << "Save " << m_map->name();
    m_map->saveToFile(m_map->project().fullpath() + "/maps/" +
                      m_map->name() + ".map");
}
