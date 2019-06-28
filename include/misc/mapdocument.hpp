#pragma once

#include <memory>

#include <QString>

namespace Dummy {
namespace Core {
class GraphicMap;
} // namespace Core
} // namespace Dummy

namespace Editor {
class Map;
class Project;
} // namespace Editor

namespace Misc {
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
};
} // namespace Misc
