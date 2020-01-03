#ifndef EDITORPROJECT_H
#define EDITORPROJECT_H

#include <memory>

#include <QDomDocument>

#include <dummy/local/project.hpp>

#include "mapDocument.hpp"
#include "mapsTreeModel.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class StartingPoint;

//////////////////////////////////////////////////////////////////////////////
//  Errors
//////////////////////////////////////////////////////////////////////////////

class ProjectError : public std::exception {};

class NoStartingPoint : public ProjectError {
public:
    const char* what() const noexcept override {
        return "the project has no starting point";
    }
};

//////////////////////////////////////////////////////////////////////////////
//  Project class
//////////////////////////////////////////////////////////////////////////////

class Project
{
public:
    Project(const std::string&);
    virtual ~Project();

    Misc::MapTreeModel* mapsModel();
    const Dummy::Local::Project& coreProject() const { return m_coreProject; }
    std::shared_ptr<Misc::MapDocument> document(const QString& mapName);
    void setModified(bool isModified) { m_isModified = isModified; }

    const StartingPoint& startingPoint() const {
        if (m_startingPoint == nullptr) {
            throw NoStartingPoint();
        }
        return *m_startingPoint;
    }

    void setStartingPoint(const StartingPoint&);
    void saveProjectFile();

    QMap<QString, std::shared_ptr<Misc::MapDocument>> openedMaps() const;

    static void create(const QString&);
    static void cleanMapName(QString& mapName);

private:
    void dumpToXmlNode(QDomDocument& document,
                        QDomElement& xmlNode,
                        QStandardItem* modelItem);

    static QDomDocument createXmlProjectTree();
    static void createXmlProjectFile(const QString&);
    static void createFolders(const QString&);

private:
    Dummy::Local::Project m_coreProject;
    QDomDocument m_domDocument;
    Misc::MapTreeModel* m_mapsModel;
    bool m_isModified;
    std::unique_ptr<StartingPoint> m_startingPoint;

    QMap<QString, std::shared_ptr<Misc::MapDocument>> m_openedMaps;
};

} // namespace Editor

#endif // EDITORPROJECT_H
