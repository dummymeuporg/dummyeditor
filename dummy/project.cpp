#include <QDebug>
#include <QDomNode>
#include <QFile>
#include <QTextStream>

#include "dummy/project.h"

Dummy::Project::Project()
{

}

void Dummy::Project::create(const QString& folder) {
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
