#ifndef EDITORPROJECT_H
#define EDITORPROJECT_H

#include <memory>

#include <QDomDocument>

#include <dummy/local/project.hpp>

#include "mapsTreeModel.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

struct MapDocument;

namespace Editor {
class StartingPoint;

//////////////////////////////////////////////////////////////////////////////
//  Errors
//////////////////////////////////////////////////////////////////////////////

class ProjectError : public std::exception
{};

//////////////////////////////////////////////////////////////////////////////
//  Project class
//////////////////////////////////////////////////////////////////////////////

class Project
{
public:
    explicit Project(const std::string& folder);
    virtual ~Project();

    // Getters
    MapsTreeModel* mapsModel();
    const Dummy::Local::Project& coreProject() const { return m_coreProject; }
    std::shared_ptr<MapDocument> document(const QString& mapName);
    QMap<QString, std::shared_ptr<MapDocument>> openedMaps() const;

    // Setters
    void setModified(bool isModified) { m_isModified = isModified; }
    void setStartingPoint(const StartingPoint&);

    void saveProject();
    static void create(const QString&);
    static void cleanMapName(QString& mapName);

private:
    void dumpToXmlNode(QDomDocument& document, QDomElement& xmlNode,
                       const QStandardItem* modelItem);

    static QDomDocument createXmlProjectTree();
    static void createXmlProjectFile(const QString&);
    static void createFolders(const QString&);

private:
    Dummy::Local::Project m_coreProject;
    QDomDocument m_domDocument;
    MapsTreeModel* m_mapsModel = nullptr;
    bool m_isModified          = false;
    std::unique_ptr<StartingPoint> m_startingPoint;

    QMap<QString, std::shared_ptr<MapDocument>> m_openedMaps;
};

} // namespace Editor

#endif // EDITORPROJECT_H
