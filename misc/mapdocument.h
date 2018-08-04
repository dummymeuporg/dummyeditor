#ifndef MAPDOCUMENT_H
#define MAPDOCUMENT_H

#include "dummy/map.h"

namespace Dummy {
    class Project;
}


namespace Misc {
    class MapDocument {
    public:
        MapDocument(const Dummy::Project& project,
                    std::shared_ptr<Dummy::Map> map = nullptr);


        std::shared_ptr<Dummy::Map> map() {
            return m_map;
        }

        void save();

        inline const Dummy::Project& project() const {
            return m_project;
        }

    private:
        const Dummy::Project& m_project;
        bool m_isModified;
        std::shared_ptr<Dummy::Map> m_map;
    };
}

#endif // MAPDOCUMENT_H
