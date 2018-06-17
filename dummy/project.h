#ifndef PROJECT_H
#define PROJECT_H

#include <QDomDocument>
#include <QString>

namespace Dummy {
    class Project
    {
    public:
        Project();

        static void create(const QString&);

    private:
        static QDomDocument _createXmlProjecTree();
    };
}

#endif // PROJECT_H
