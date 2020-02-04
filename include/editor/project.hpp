#ifndef EDITORPROJECT_H
#define EDITORPROJECT_H

#include <QDomDocument>
#include <QMap>
#include <memory>

#include <dummy/local/project.hpp>

#include "editor/startingPoint.hpp"
#include "mapsTree.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

struct MapDocument;

namespace Editor {
class StartingPoint;

//////////////////////////////////////////////////////////////////////////////
//  Project class
//////////////////////////////////////////////////////////////////////////////
struct tMapInfo
{
    std::string m_mapName;
    std::string m_chispetPath;
    std::string m_musicPath;
    uint16_t m_width  = 0;
    uint16_t m_height = 0;
};

class Project
{
public:
    explicit Project(const std::string& folder);

    // Getters
    MapsTreeModel* mapsModel();
    const Dummy::Local::Project& coreProject() const { return m_coreProject; }
    const MapDocument& document(const QString& mapName);
    QMap<QString, std::shared_ptr<MapDocument>> openedMaps() const;

    // Setters
    void setModified(bool isModified) { m_isModified = isModified; }
    void setStartingPoint(const StartingPoint&);

    // Utils
    void saveProject();
    static void create(const QString&);
    static void cleanMapName(QString& mapName);
    void createMap(const tMapInfo& mapInfo, QStandardItem& parent);

private:
    void dumpToXmlNode(QDomDocument& document, QDomElement& xmlNode, const QStandardItem* modelItem);

    static QDomDocument createXmlProjectTree();
    static void createXmlProjectFile(const QString&);
    static void createFolders(const QString&);

private:
    Dummy::Local::Project m_coreProject;
    QDomDocument m_domDocument;
    std::unique_ptr<MapsTreeModel> m_mapsModel;
    bool m_isModified = false;
    StartingPoint m_startingPoint;

    QMap<QString, std::shared_ptr<MapDocument>> m_openedMaps;
};

} // namespace Editor

#endif // EDITORPROJECT_H
