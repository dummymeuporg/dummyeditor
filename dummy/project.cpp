#include <algorithm>

#include <QDebug>
#include <QDir>
#include <QDomNode>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "misc/treeitem.h"
#include "misc/treemodel.h"

#include "dummy/project.h"

Dummy::Project::Project(const QString& folderPath) :
    m_mapsModel(nullptr)
{
    Q_UNUSED(folderPath);
    // Try to read the "project.xml" file that should be present in folderPath.
    QFile xmlProjectFile(folderPath + "/project.xml");
    m_domDocument.setContent(&xmlProjectFile);
    xmlProjectFile.close();

    QDomNodeList mapsNodes = m_domDocument
        .documentElement()
        .elementsByTagName("maps");

    if (mapsNodes.length() > 0) {
        m_mapsModel = new Misc::TreeModel(mapsNodes.at(0), nullptr);
    } else {
        // TODO: Throw exception?
    }
}

Misc::TreeModel* Dummy::Project::mapsModel() {
    return m_mapsModel;
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
