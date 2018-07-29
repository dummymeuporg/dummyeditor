#ifndef MAPDOCUMENT_H
#define MAPDOCUMENT_H

#include "dummy/map.h"

namespace Dummy {
    class Project;
}


namespace Misc {
    class MapDocument {
    public:
        MapDocument(Dummy::Project* project = nullptr,
                    std::shared_ptr<Dummy::Map> map = nullptr);
        MapDocument(const MapDocument&);

        std::shared_ptr<Dummy::Map> map() {
            return m_map;
        }

        void save();

    private:
        Dummy::Project* m_project;
        bool m_isModified;
        std::shared_ptr<Dummy::Map> m_map;
    };
}

#endif // MAPDOCUMENT_H
