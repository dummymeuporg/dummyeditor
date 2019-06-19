#include <algorithm>

#include <QDebug>
#include <QDir>
#include <QDomNode>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "editormap.hpp"
#include "misc/maptreemodel.hpp"

#include "editorproject.hpp"
#include "editorstartingpoint.hpp"

EditorProject::EditorProject(const std::string& projectFolder)
    : m_coreProject(fs::path(projectFolder)),
      m_mapsModel(nullptr)
{

    // Try to read the "project.xml" file that should be present in folderPath.
    QFile xmlProjectFile(
        (m_coreProject.projectPath() / "project.xml").string().c_str()
    );
    m_domDocument.setContent(&xmlProjectFile);
    xmlProjectFile.close();

    QDomNodeList mapsNodes = m_domDocument
        .documentElement()
        .elementsByTagName("maps");

    if (mapsNodes.length() > 0) {
        m_mapsModel = new Misc::MapTreeModel(mapsNodes.at(0));
    } else {
        // XXX: Throw exception?
    }

    QDomNodeList startingPositionNodes = m_domDocument.documentElement()
        .elementsByTagName("starting_point");

    if (startingPositionNodes.length() > 0)
    {
        const QDomNode& startingPositionNode(startingPositionNodes.at(0));
        const QDomNamedNodeMap& attributes(startingPositionNode.attributes());
        m_startingPoint = std::make_unique<EditorStartingPoint>(
            attributes.namedItem("map").nodeValue().toStdString().c_str(),
            attributes.namedItem("x").nodeValue().toUShort(),
            attributes.namedItem("y").nodeValue().toUShort());
    }
}

EditorProject::~EditorProject() {

    delete m_mapsModel;
}

Misc::MapTreeModel* EditorProject::mapsModel() {
    return m_mapsModel;
}

void EditorProject::setStartingPoint(
    const EditorStartingPoint& startingPoint)
{
    m_startingPoint = std::make_unique<EditorStartingPoint>(startingPoint);
}

void EditorProject::create(const QString& folder) {
    _createXmlProjectFile(folder);
    _createFolders(folder);

}

void EditorProject::_createXmlProjectFile(const QString& folder) {
    QFile projectFile(folder + "/" + "project.xml");
    projectFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&projectFile);
    out << _createXmlProjectTree().toString(4);
    projectFile.close();
}

QDomDocument EditorProject::_createXmlProjectTree() {
    QDomDocument doc;
    QDomElement project = doc.createElement("project");
    QDomElement maps = doc.createElement("maps");

    doc.appendChild(project);
    project.appendChild(maps);

    return doc;
}

void EditorProject::_createFolders(const QString& baseFolder) {
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

void EditorProject::saveProjectFile() {
    QDomDocument doc;
    QDomElement projectNode = doc.createElement("project");
    QDomElement mapsNode = doc.createElement("maps");

    doc.appendChild(projectNode);
    projectNode.appendChild(mapsNode);

    if (nullptr != m_startingPoint)
    {
        QDomElement startingPointNode = doc.createElement("starting_point");
        startingPointNode.setAttribute("map", m_startingPoint->mapName());
        startingPointNode.setAttribute("x", m_startingPoint->x());
        startingPointNode.setAttribute("y", m_startingPoint->y());
        projectNode.appendChild(startingPointNode);
    }

    _dumpToXmlNode(doc, mapsNode, m_mapsModel->invisibleRootItem());
    QString xmlPath(
        (m_coreProject.projectPath() / "project.xml").string().c_str()
    );

    // XXX: Handle errors eventually.
    QFile file(xmlPath);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&file);
    doc.save(stream, 4);
}

void EditorProject::_dumpToXmlNode(QDomDocument& doc,
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

void EditorProject::cleanMapName(QString& mapName) {
    mapName.replace("/", "");
    mapName.replace("..", "");
}

std::shared_ptr<Misc::MapDocument>
EditorProject::document(const QString& mapName) {
    QString cleantMapname(mapName);
    cleanMapName(cleantMapname);

    if (!m_openedMaps.contains(cleantMapname)) {
        auto map = std::make_shared<EditorMap>(
            m_coreProject, cleantMapname.toStdString()
        );
        map->load();

        auto mapDocument = std::make_shared<Misc::MapDocument>(
            *this, cleantMapname, map
        );

        m_openedMaps.insert(cleantMapname, mapDocument);
    }
    return m_openedMaps[cleantMapname];
}
