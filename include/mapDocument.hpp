#ifndef MAPDOCUMENT_H
#define MAPDOCUMENT_H

#include <memory>
#include <vector>

#include <QString>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class GraphicLayer;
} // namespace GraphicMap

namespace Editor {
class Map;
class Project;
} // namespace Editor

using GraphicLayers = std::vector<std::shared_ptr<::GraphicMap::GraphicLayer>>;

//////////////////////////////////////////////////////////////////////////////
//  MapDocument class
//////////////////////////////////////////////////////////////////////////////

class MapDocument
{
public:
    MapDocument(Editor::Project&, const QString&, std::shared_ptr<Editor::Map>);

    std::shared_ptr<Editor::Map> map() { return m_map; }
    Editor::Project& project() { return m_editorProject; }
    const QString mapName() const { return m_mapName; }

    void save();


private:
    Editor::Project& m_editorProject;
    bool m_isModified;
    QString m_mapName;
    std::shared_ptr<Editor::Map> m_map;
    GraphicLayers m_graphicLayers;
};

#endif // MAPDOCUMENT_H
