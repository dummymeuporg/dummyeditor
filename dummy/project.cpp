#include <algorithm>

#include <QDebug>
#include <QDir>
#include <QDomNode>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "dummy/project.h"

Dummy::Project::Project(const QString& folderPath)
{
    Q_UNUSED(folderPath);
    // Try to read the "project.xml" file that should be present in folderPath.

}

void Dummy::Project::create(const QString& folder) {
    Dummy::Project::_createXmlProjectFile(folder);
    Dummy::Project::_createFolders(folder);

}

void Dummy::Project::_createXmlProjectFile(const QString& folder) {
    QFile projectFile(folder + "/" + "project.xml");
    projectFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&projectFile);
    out << Project::_createXmlProjecTree().toString(4);
    projectFile.close();
}

QDomDocument Dummy::Project::_createXmlProjecTree() {
    QDomDocument doc;
    QDomElement project = doc.createElement("project");
    QDomElement maps = doc.createElement("maps");

    doc.appendChild(project);
    project.appendChild(maps);

    return doc;
}

void Dummy::Project::_createFolders(const QString& baseFolder) {
    std::vector<QString> folders{"maps", "chipsets", "sounds"};
    std::for_each(folders.begin(), folders.end(),
                  [&baseFolder](const QString& folder) {
        QDir dir(baseFolder + "/" + folder);
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        qDebug() << "create folder " << folder;
    });
}
