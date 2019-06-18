#pragma once

#include <memory>

#include <QString>

namespace Dummy {
namespace Core {
class GraphicMap;
} // namespace Core
} // namespace Dummy

class EditorMap;
class EditorProject;

namespace Misc {
class MapDocument {
public:
    MapDocument(EditorProject&,
                const QString&,
                std::shared_ptr<EditorMap>);


    std::shared_ptr<EditorMap> map() {
        return m_map;
    }

    void save();

    EditorProject& project() {
        return m_editorProject;
    }

    inline const QString mapName() const {
        return m_mapName;
    }

private:
    EditorProject& m_editorProject;
    bool m_isModified;
    QString m_mapName;
    std::shared_ptr<EditorMap> m_map;
};
} // namespace Misc
