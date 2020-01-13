#include "mapDocument.hpp"

#include <QDebug>

#include "editor/map.hpp"

MapDocument::MapDocument(Editor::Project& project, const QString& name,
                         std::shared_ptr<Editor::Map> map)
    : project(project)
    , map(map)
    , mapName(name)
{}
