#ifndef PROJECT_H
#define PROJECT_H

#include <memory>

#include <QDomDocument>
#include <QString>

#include "misc/treemodel.h"

namespace Dummy {
    class Project
    {
    public:
        Project(const QString& projectFolder);
        virtual ~Project();
        static void create(const QString&);
        Misc::TreeModel* mapsModel();

        inline const QString& fullpath() const {
            return m_fullpath;
        }

    private:
        QString m_fullpath;
        QDomDocument m_domDocument;
        Misc::TreeModel* m_mapsModel;
        static QDomDocument _createXmlProjecTree();
        static void _createXmlProjectFile(const QString&);
        static void _createFolders(const QString&);

    };
}

#endif // PROJECT_H
