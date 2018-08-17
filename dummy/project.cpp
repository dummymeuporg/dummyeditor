#include <algorithm>

#include <QDebug>
#include <QDir>
#include <QDomNode>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "misc/maptreemodel.h"

#include "dummy/project.h"

Dummy::Project::Project(const QString& folderPath) :
    m_fullpath(folderPath), m_mapsModel(nullptr)
{

    // Try to read the "project.xml" file that should be present in folderPath.
    QFile xmlProjectFile(folderPath + "/project.xml");
    m_domDocument.setContent(&xmlProjectFile);
    xmlProjectFile.close();

    QDomNodeList mapsNodes = m_domDocument
        .documentElement()
        .elementsByTagName("maps");

    if (mapsNodes.length() > 0) {
        m_mapsModel = new Misc::MapTreeModel(mapsNodes.at(0));
    } else {
        // TODO: Throw exception?
    }
}

Dummy::Project::~Project() {

    delete m_mapsModel;
}

Misc::MapTreeModel* Dummy::Project::mapsModel() {
    return m_mapsModel;
}

void Dummy::Project::setStartingPoint(
    const Dummy::StartingPoint& startingPoint)
{
    m_startingPoint = std::make_unique<Dummy::StartingPoint>(startingPoint);
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

void Dummy::Project::saveProjectFile() {
    QDomDocument doc;
    QDomElement projectNode = doc.createElement("project");
    QDomElement mapsNode = doc.createElement("maps");

    doc.appendChild(projectNode);
    projectNode.appendChild(mapsNode);

    _dumpToXmlNode(doc, mapsNode, m_mapsModel->invisibleRootItem());
    QString xmlPath(m_fullpath + "/project.xml");

    // XXX: Handle errors eventually.
    QFile file(xmlPath);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&file);
    doc.save(stream, 4);
}

void Dummy::Project::_dumpToXmlNode(QDomDocument& doc,
                                    QDomElement& xmlNode,
                                    QStandardItem* modelItem) {

    for(int i = 0; i < modelItem->rowCount(); ++i) {
        QStandardItem* mapItem = modelItem->child(i);

        QDomElement mapNode = doc.createElement("map");
        mapNode.setAttribute("name", mapItem->text());

        xmlNode.appendChild(mapNode);

        _dumpToXmlNode(doc, mapNode, mapItem);
    }
}

void Dummy::Project::cleanMapName(QString& mapName) {
    mapName.replace("/", "");
    mapName.replace("..", "");
}

std::shared_ptr<Misc::MapDocument>&
Dummy::Project::document(const QString& mapName) {
    QString cleantMapname(mapName);
    cleanMapName(cleantMapname);

    if (!m_openedMaps.contains(cleantMapname)) {

        std::shared_ptr<Map> map(Dummy::Map::loadFromFile(
            *this,
            m_fullpath + "/maps/" + cleantMapname + ".map"));
        map->setName(cleantMapname);

        std::shared_ptr<Misc::MapDocument> mapDocument(
            new Misc::MapDocument(*this, map));

        m_openedMaps.insert(cleantMapname, mapDocument);
    }
    return m_openedMaps[cleantMapname];
}
