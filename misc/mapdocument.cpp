#include "mapdocument.h"

Misc::MapDocument::MapDocument(Dummy::Project* project,
                               std::shared_ptr<Dummy::Map> map)
    : m_project(project), m_map(map)
{
}

Misc::MapDocument::MapDocument(const MapDocument& document)
    : m_project(document.m_project), m_map(document.m_map)
{
}
