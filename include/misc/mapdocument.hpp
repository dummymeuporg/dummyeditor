#pragma once

#include <memory>
#include <vector>

#include <QString>

namespace Dummy {
namespace Core {
class GraphicMap;
} // namespace Core
} // namespace Dummy

namespace GraphicMap {
class GraphicLayer;
} // namespace GraphicMap;

namespace Editor {
class Map;
class Project;
} // namespace Editor

namespace Misc {

using GraphicLayers = std::vector<std::shared_ptr<::GraphicMap::GraphicLayer>>;

class MapDocument {
public:
    MapDocument(Editor::Project&,
                const QString&,
                std::shared_ptr<Editor::Map>);


    std::shared_ptr<Editor::Map> map() {
        return m_map;
    }

    void save();

    Editor::Project& project() {
        return m_editorProject;
    }

    inline const QString mapName() const {
        return m_mapName;
    }

private:
    Editor::Project& m_editorProject;
    bool m_isModified;
    QString m_mapName;
    std::shared_ptr<Editor::Map> m_map;
    GraphicLayers m_graphicLayers;
};
} // namespace Misc
