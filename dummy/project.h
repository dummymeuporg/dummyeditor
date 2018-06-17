#ifndef PROJECT_H
#define PROJECT_H

#include <QDomDocument>
#include <QString>

namespace Dummy {
    class Project
    {
    public:
        Project(const QString& projectFolder);

        static void create(const QString&);

    private:
        static QDomDocument _createXmlProjecTree();
        static void _createXmlProjectFile(const QString&);
        static void _createFolders(const QString&);

    };
}

#endif // PROJECT_H
