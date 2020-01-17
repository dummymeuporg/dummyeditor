#include "editor/project.hpp"

#include <algorithm>

#include <QDebug>
#include <QDir>

#include "editor/map.hpp"
#include "editor/startingPoint.hpp"
#include "mapDocument.hpp"
#include "mapsTreeModel.hpp"

namespace Editor {

Project::Project(const std::string& projectFolder)
    : m_coreProject(fs::path(projectFolder))
{
    // Try to read the "project.xml" file that should be present in folderPath.
    QFile xmlProjectFile(
        (m_coreProject.projectPath() / "project.xml").string().c_str());
    m_domDocument.setContent(&xmlProjectFile);
    xmlProjectFile.close();

    QDomNodeList mapsNodes =
        m_domDocument.documentElement().elementsByTagName("maps");

    if (mapsNodes.length() > 0) {
        m_mapsModel = new MapsTreeModel(mapsNodes.at(0));
    } else {
        // XXX: Throw exception?
    }

    QDomNodeList startingPositionNodes =
        m_domDocument.documentElement().elementsByTagName("starting_point");

    if (startingPositionNodes.length() > 0) {
        const QDomNode& startingPositionNode(startingPositionNodes.at(0));
        const QDomNamedNodeMap& attributes(startingPositionNode.attributes());
        m_startingPoint = std::make_unique<StartingPoint>(
            attributes.namedItem("map").nodeValue().toStdString().c_str(),
            attributes.namedItem("x").nodeValue().toUShort(),
            attributes.namedItem("y").nodeValue().toUShort(),
            attributes.namedItem("floor").nodeValue().toUShort());
    }
}

Project::~Project()
{
    delete m_mapsModel;
}

MapsTreeModel* Project::mapsModel()
{
    return m_mapsModel;
}

QMap<QString, std::shared_ptr<MapDocument>> Project::openedMaps() const
{
    return m_openedMaps;
}

void Project::setStartingPoint(const StartingPoint& startingPoint)
{
    m_startingPoint = std::make_unique<StartingPoint>(startingPoint);
}

void Project::create(const QString& folder)
{
    createXmlProjectFile(folder);
    createFolders(folder);
}

void Project::createXmlProjectFile(const QString& folder)
{
    QFile projectFile(folder + "/" + "project.xml");
    projectFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&projectFile);
    const int indent = 4;
    out << createXmlProjectTree().toString(indent);
    projectFile.close();
}

QDomDocument Project::createXmlProjectTree()
{
    QDomDocument doc;
    QDomElement project = doc.createElement("project");
    QDomElement maps    = doc.createElement("maps");

    doc.appendChild(project);
    project.appendChild(maps);

    return doc;
}

void Project::createFolders(const QString& baseFolder)
{
    std::vector<QString> folders {"maps", "chipsets", "sounds"};
    std::for_each(folders.begin(), folders.end(),
                  [&baseFolder](const QString& folder) {
                      QDir dir(baseFolder + "/" + folder);
                      if (! dir.exists()) {
                          dir.mkpath(".");
                      }
                      qDebug() << "create folder " << folder;
                  });
}

void Project::saveProject()
{
    QDomDocument doc;
    QDomElement projectNode = doc.createElement("project");
    QDomElement mapsNode    = doc.createElement("maps");

    doc.appendChild(projectNode);
    projectNode.appendChild(mapsNode);

    if (nullptr != m_startingPoint) {
        QDomElement startingPointNode = doc.createElement("starting_point");
        startingPointNode.setAttribute("map", m_startingPoint->mapName());
        startingPointNode.setAttribute("x", m_startingPoint->x());
        startingPointNode.setAttribute("y", m_startingPoint->y());
        startingPointNode.setAttribute(
            "floor", static_cast<std::uint16_t>(m_startingPoint->floor()));
        projectNode.appendChild(startingPointNode);
    }

    dumpToXmlNode(doc, mapsNode, m_mapsModel->invisibleRootItem());
    QString xmlPath(
        (m_coreProject.projectPath() / "project.xml").string().c_str());

    // XXX: Handle errors eventually.
    QFile file(xmlPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    const int indent = 4;
    doc.save(stream, indent);

    if (openedMaps().count() > 0) {
        for (auto e : openedMaps().keys()) {
            document(e)->map->save();
        }
    }
}

void Project::dumpToXmlNode(QDomDocument& doc, QDomElement& xmlNode,
                            QStandardItem* modelItem)
{
    for (int i = 0; i < modelItem->rowCount(); ++i) {
        QStandardItem* mapItem = modelItem->child(i);

        QDomElement mapNode = doc.createElement("map");
        mapNode.setAttribute("name", mapItem->text());

        xmlNode.appendChild(mapNode);

        dumpToXmlNode(doc, mapNode, mapItem);
    }
}

void Project::cleanMapName(QString& mapName)
{
    mapName.replace("\\", "");
    mapName.replace("/", "");
    mapName.replace("..", "");
}

std::shared_ptr<MapDocument> Project::document(const QString& mapName)
{
    QString cleantMapname(mapName);
    cleanMapName(cleantMapname);

    if (! m_openedMaps.contains(cleantMapname)) {
        auto map = std::make_shared<Editor::Map>(m_coreProject,
                                                 cleantMapname.toStdString());
        map->load();

        auto mapDocument =
            std::make_shared<MapDocument>(*this, cleantMapname, map);

        m_openedMaps.insert(cleantMapname, mapDocument);
    }
    return m_openedMaps[cleantMapname];
}
} // namespace Editor
