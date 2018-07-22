#ifndef PROJECT_H
#define PROJECT_H

#include <memory>

#include <QDomDocument>
#include <QMap>
#include <QString>

#include "misc/mapdocument.h"
#include "misc/maptreemodel.h"

namespace Dummy {
    class Project
    {
    public:
        Project(const QString& projectFolder);
        virtual ~Project();
        static void create(const QString&);
        Misc::MapTreeModel* mapsModel();

        inline const QString& fullpath() const {
            return m_fullpath;
        }

        inline bool isModified() const {
            return m_isModified;
        }

        Project& setModified(bool isModified) {
            m_isModified = isModified;
            return *this;
        }

        void saveProjectFile();

    private:
        QString m_fullpath;
        QDomDocument m_domDocument;
        Misc::MapTreeModel* m_mapsModel;
        bool m_isModified;

        QMap<QString, std::shared_ptr<Misc::MapDocument>> m_openedMaps;

        static QDomDocument _createXmlProjecTree();
        static void _createXmlProjectFile(const QString&);
        static void _createFolders(const QString&);
        void _dumpToXmlNode(QDomDocument& document,
                            QDomElement& xmlNode,
                            QStandardItem* modelItem);


    };
}

#endif // PROJECT_H
