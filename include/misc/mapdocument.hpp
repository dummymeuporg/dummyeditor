#pragma once

#include <memory>

namespace Dummy {
namespace Core {
class GraphicMap;
} // namespace Core
} // namespace Dummy

class EditorProject;

namespace Misc {
class MapDocument {
public:
    MapDocument(EditorProject&,
                std::unique_ptr<Dummy::Core::GraphicMap>);


    Dummy::Core::GraphicMap& map() {
        return *m_map;
    }

    void save();

    EditorProject& project() {
        return m_editorProject;
    }

private:
    EditorProject& m_editorProject;
    bool m_isModified;
    std::unique_ptr<Dummy::Core::GraphicMap> m_map;
};
} // namespace Misc
